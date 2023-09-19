/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:01:37 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/19 18:12:14 by ffornes-         ###   ########.fr       */
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

void	ctrl_c(int mode)
{
	struct termios	tc;

	tcgetattr(0, &tc);
	tc.c_lflag &= ~ECHOCTL;
	if (mode)
		tc.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &tc);
}

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

static int	main_loop(char *prompt, char **envp)
{
	char	*input;
	t_list	*list;

	set_or_return_state(MODE_SET, STATE_READ);
	ctrl_c(MODE_UNSET);
	signal_handler();
	input = readline(prompt);
	if (!input)
		builtin_exit(NULL);
	if (input[0] != '\0')
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		add_history(input);
		set_or_return_exit_status(MODE_SET, parse_input(input, envp, &list));
		if (!set_or_return_exit_status(MODE_RETURN, -1))
		{
			list = organize_list(list);
			cmp_commands(list, envp);
			ft_lstclear(&list, (void *)free_token);
		}
	}
	free(input);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*prompt;
	t_data	data;

	if (argc > 1)
		return (1);
	init_data(&data, envp);
	if (!data.env)
		return (print_and_return(12));
	prompt = ft_strjoin((argv[0] + 2), "$ ");
	if (!prompt)
	{
		free_double((void **)data.env);
		return (print_and_return(12));
	}
	set_or_return_exit_status(MODE_SET, 0);
	while (42)
		if (main_loop(prompt, data.env))
			break ;
	free_double((void **)data.env);
	free(prompt);
	clear_history();
	return (set_or_return_exit_status(MODE_RETURN, -1));
}
