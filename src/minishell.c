/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:01:37 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/18 19:49:17 by ffornes-         ###   ########.fr       */
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

static char	**set_env(char *env[])
{
	int		i;
	char	**dst;

	i = 0;
	while (env[i])
		i++;
	dst = malloc(sizeof(char *) * (i + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (env[i])
	{
		dst[i] = ft_strdup(env[i]);
		if (!dst[i++])
		{
			free_double((void **)dst);
			return (NULL);
		}
	}
	dst[i] = NULL;
	return (dst);
}

int	exit_check(char *input) // Make builtin
{
	if (!ft_strncmp(input, "exit\0", 5))
	{
		free(input);
		printf("exit\n");
		ctrl_c(MODE_SET);
		return (1);
	}
	return (0);
}

static int	main_loop(char *prompt, char **envp)
{
	char	*input;
	t_list	*list;

	set_or_return_state(MODE_SET, STATE_READ);
	ctrl_c(MODE_UNSET);
	signal_handler();
	input = readline(prompt);
	if (!input)
		return (1);
	if (input[0] != '\0')
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		add_history(input);
		if (exit_check(input))
			return (1);
		set_or_return_exit_status(MODE_SET, parse_input(input, envp, &list));
		if (!set_or_return_exit_status(MODE_RETURN, -1))
		{
			list = organize_list(list);
			print_tokens(list); // Debug
			cmp_commands(list, envp); // Send &state & update value when executing || here_doc
			ft_lstclear(&list, (void *)free_token);
		}
	}
	free(input);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*prompt;
	char	**my_env;

	if (argc > 1)
		return (1);
	my_env = set_env(envp);
	if (!my_env)
		return (print_and_return(12));
	prompt = ft_strjoin((argv[0] + 2), "$ ");
	if (!prompt)
	{
		free_double((void **)my_env);
		return (print_and_return(12));
	}
	set_or_return_exit_status(MODE_SET, 0);
	while (42)
		if (main_loop(prompt, my_env))
			break ;
	free_double((void **)my_env);
	free(prompt);
	clear_history();
	return (set_or_return_exit_status(MODE_RETURN, -1));
}
