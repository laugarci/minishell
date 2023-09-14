/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:01:37 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/14 17:28:35 by ffornes-         ###   ########.fr       */
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
#include "parser.h"

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

static int	exit_check(char *input) // Make builtin
{
	if (!ft_strncmp(input, "exit\0", 5))
	{
		free(input);
		printf("exit\n");
		return (1);
	}
	return (0);
}

static int	main_loop(char *prompt, char **envp, int *exit_status)
{
	char	*input;
	t_list	*list;

	input = readline(prompt);
	if (!input)
		return (1);
	if (input[0] != '\0')
	{
		add_history(input);
		if (exit_check(input))
			return (1);
		*exit_status = parse_input(input, envp, &list, exit_status);
		if (*exit_status == 0)
		{
			//print_tokens(list);
			cmp_commands(list, envp);
			ft_lstclear(&list, (void *)free_token);
		}
		printf("EXIT STATUS: %d\n", *exit_status);
	}
	free(input);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*prompt;
	int		exit_status;
	char	**my_env;

	exit_status = 0;
	if (argc > 1)
		return (1);
	my_env = set_env(envp);
	if (!my_env)
		return (12);
	prompt = ft_strjoin((argv[0] + 2), "$ ");
	if (!prompt)
		return (12);
	while (42)
		if (main_loop(prompt, my_env, &exit_status))
			break ;
	free_double((void **)my_env);
	free(prompt);
	clear_history();
	return (0);
}
