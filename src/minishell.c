/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:52:21 by laugarci          #+#    #+#             */
/*   Updated: 2023/07/05 12:50:27 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

static char	**set_env(char **src)
{
	int		i;
	char	**dst;

	i = 0;
	while (src[i])
		i++;
	dst = malloc(sizeof(char **) * (i + 1));
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

static void	exit_check(char *input)
{
	if (!ft_strncmp(input, "exit\0", 5))
	{
		free(input);
		exit(0);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;
	char	*prompt;
	char	**env;

	if (argc > 1)
		exit(1);
	env = set_env(envp);
	if (!env) // mem error
		return (1);
	prompt = ft_strjoin(argv[0], " > ");
	if (!prompt)
		return (1);
	while (1)
	{
		input = readline(prompt);
		if (input[0] != '\0' && input)
		{
			add_history(input);
			exit_check(input);
			parse_input(input, envp);
			exec_commands(input, env);
		}
		free(input);
	}
	clear_history();
	return (0);
}
