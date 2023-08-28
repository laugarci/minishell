/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:01:37 by laugarci          #+#    #+#             */
/*   Updated: 2023/08/28 11:36:53 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "libft.h"
#include "libft_bonus.h"
#include "minishell.h"
#include "minishell_defs.h"
#include "parser.h"

/// AJNKNAEKK DEBUGGGGGGGGGGGG
static void	print_tokens(t_list *lst)
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
		else if (token->type == O_APPEND)
			printf("O_APPEND]");
		else if (token->type == O_TRUNC)
			printf("O_TRUNC]");
		else
			printf("-1]");
		printf("\t[Quotes: %d]\n", token->quotes);
		lst = lst->next;
		token = lst->content;
		if (!token->string)
			break ;
	}
} // DEBUG DEBUG DEBUG DEBUG DELETE LATER   RR ER E REA EGAG 

static int	set_env(t_data *data, char *env[])
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	data->envp = malloc(sizeof(char *) * (i + 1));
	if (!data->envp)
		return (1);
	i = 0;
	while (env[i])
	{
		data->envp[i] = ft_strdup(env[i]);
		if (!data->envp[i++])
		{
			free_double((void **)data->envp);
			return (1);
		}
	}
	data->envp[i] = NULL;
	return (0);
}

static int	exit_check(char *input)
{
	if (!ft_strncmp(input, "exit\0", 5))
	{
		free(input);
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;
	char	*prompt;
	t_data	data;
	t_list	*list;

	if (argc > 1)
		return (1);
	if (set_env(&data, envp)) // Error: Not enough memory
		return (1);
	prompt = ft_strjoin((argv[0] + 2), "$ ");
	if (!prompt)
		return (1);
	while (42)
	{
		input = readline(prompt);
		if (!input)
			break ;
		if (input[0] != '\0')
		{
			add_history(input);
			if (exit_check(input))
				break ;
			if (!parse_input(input, data.envp, &list))
			{
				print_tokens(list);
				cmp_commands(list, data.envp);
				ft_lstclear(&list, (void *)free_token);
			}
			free(input);
		}
		else
			free(input);
	}
	free_double((void **)data.envp);
	free(prompt);
	clear_history();
	return (0);
}
