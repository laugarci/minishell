/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:01:37 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/25 17:04:02 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "libft.h"
#include "libft_bonus.h"
#include "minishell.h"
#include "minishell_defs.h"
#include "parser.h"
#include "termios.h"

static int	main_loop(char *prompt, t_list **env_lst)
{
	char	*input;
	char	**environ;
	t_list	*list;

	environ = envlst_to_charpp(*env_lst);
	if (!environ)
		return (print_and_return(12));
	set_or_return_state(MODE_SET, STATE_READ);
	signal_display(MODE_UNSET);
	signal_handler();
	input = readline(prompt);
	if (!input)
		builtin_exit(NULL);
	if (input[0] != '\0')
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		add_history(input);
		set_or_return_exit_status(MODE_SET, parse_input(input, environ, &list));
		if (!set_or_return_exit_status(MODE_RETURN, -1))
		{
			list = organize_list(list);
			start_execution(list, env_lst, environ);
			ft_lstclear(&list, (void *)free_token);
		}
	}
	free_double((void **)environ);
	free(input);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*prompt;
	t_list	*env_lst;

	if (argc > 1)
		return (1);
	env_lst = set_env(envp);
	if (!env_lst)
		return (print_and_return(12));
	prompt = ft_strjoin((argv[0] + 2), "$ ");
	if (!prompt)
	{
		ft_lstclear(&env_lst, (void *)free_var);
		return (print_and_return(12));
	}
	set_or_return_exit_status(MODE_SET, 0);
	while (42)
		if (main_loop(prompt, &env_lst))
			break ;
	ft_lstclear(&env_lst, (void *)free_var);
	free(prompt);
	clear_history();
	return (set_or_return_exit_status(MODE_RETURN, -1));
}
