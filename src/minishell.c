/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:01:37 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/27 10:59:32 by ffornes-         ###   ########.fr       */
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

// AJNKNAEKK DEBUGGGGGGGGGGGG // INCLUDED IN PARSER.H
void	print_tokens(t_list *lst)
{
	t_token		*token;

	token = lst->content;
	while (1)
	{
		printf("Token = [String: %s]\t", token->string);
		printf("[Type: ");
		if (token->type == INFILE)
			printf("INFILE]");
		else if (token->type == HERE_DOC)
			printf("H_DOC]");
		else if (token->type == PIPE)
			printf("PIPE]");
		else if (token->type == APPEND)
			printf("APPEND]");
		else if (token->type == TRUNC)
			printf("TRUNC]");
		else if (token->type == TOKEN_APPEND)
			printf("TOKEN_APPEND]");
		else if (token->type == TOKEND)
			printf("TOKEND]");
		else
			printf("-1]");
		printf("\t[Quotes: %d]\n", token->quotes);
		if (!lst->next)
			break ;
		lst = lst->next;
		token = lst->content;
		if (!token->string)
			break ;
	}
}
// DEBUG DEBUG DEBUG DEBUG DELETE LATER   RR ER E REA EGAG */

static int	main_loop(char *prompt, t_list **env_lst)
{
	char	*input;
	char	**environ;
	t_list	*list;
	int		err;

	environ = envlst_to_charpp(*env_lst);
	if (!environ)
		return (print_error_and_return("Cannot allocate memory\n", 12));
	set_or_return_state(MODE_SET, STATE_READ);
	signal_display(MODE_UNSET);
	signal_handler();
	input = readline(prompt);
	if (!input)
		builtin_exit(ft_itoa(set_or_return_exit_status(MODE_RETURN, -1)));
	if (input[0] != '\0')
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		add_history(input);
		err = parse_input(input, environ, &list);
		if (!err)
		{
			list = organize_list(list);
			start_execution(list, env_lst, environ);
			ft_lstclear(&list, (void *)free_token);
		}
		else
			set_or_return_exit_status(MODE_SET, err);
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
		return (print_error_and_return("Cannot allocate memory\n", 12));
	prompt = ft_strjoin((argv[0] + 2), "$ ");
	if (!prompt)
	{
		ft_lstclear(&env_lst, (void *)free_var);
		return (print_error_and_return("Cannot allocate memory\n", 12));
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
