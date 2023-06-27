/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:52:21 by laugarci          #+#    #+#             */
/*   Updated: 2023/06/27 12:09:56 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

static void	free_double(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

/* Error: Unable to read from envp variable... wtf */
int	main(int argc, char *argv[], char *envp[])
{
	char	*input;
	char	*aux;
	char	**tmp;

	if (argc > 1)
		exit(1);
	argv = NULL;
	// REMEMBER ARGV IS NULL HERE PLSSSS
	while (1)
	{
		input = readline("minishell > ");
		if (!ft_strncmp(input, "exit\0", 5))
		{
			free(input);
			exit(0);
		}
		tmp = ft_split(input, ' ');
		aux = get_path(tmp, envp);
		if (aux)
		{
			printf("Path found: %s\n", aux);
			free(aux);
		}
		free_double(tmp);
		free(input);
	}
	return (0);
}
