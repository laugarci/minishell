/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2023/07/05 14:01:37 by laugarci          #+#    #+#             */
/*   Updated: 2023/08/04 09:57:06 by laugarci         ###   ########.fr       */
=======
/*   Created: 2023/08/04 14:01:16 by laugarci          #+#    #+#             */
/*   Updated: 2023/08/10 11:59:18 by laugarci         ###   ########.fr       */
>>>>>>> new_exec
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "libft.h"
#include "libft_bonus.h"
#include "minishell.h"
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

static char	**set_env(char **src)
{
	int		i;
	char	**dst;

	i = 0;
	while (src[i])
		i++;
	dst = malloc(sizeof(char *) * (i + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i++])
		{
			free_double((void **)dst);
			return (NULL);
		}
	}
	dst[i] = NULL;
	return (dst);
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
	char	**env;
	t_list	*list;

	if (argc > 1)
		return (1);
	env = set_env(envp);
	if (!env) // mem error
		return (1);
	prompt = ft_strjoin((argv[0] + 2), "$ ");
	if (!prompt)
		return (1);
	while (42)
	{
		input = readline(prompt);
		if (input[0] != '\0' && input)
		{
			add_history(input);
			if (exit_check(input))
				break ;
			if (!parse_input(input, env, &list))
			{
				print_tokens(list);
				cmp_commands(list, env);
				ft_lstclear(&list, (void *)free_token);
			}
		}
		else
			free(input);
	}
	free_double((void **)env);
	free(prompt);
	clear_history();
	return (0);
}
