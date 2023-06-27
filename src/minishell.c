/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:52:21 by laugarci          #+#    #+#             */
/*   Updated: 2023/06/27 14:49:16 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

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

	argv = NULL;	// REMEMBER ARGV IS NULL HERE PLSSSS
	if (argc > 1)
		exit(1);
	while (1)
	{
		input = readline("minishell > ");
		if (input[0] != '\0' && input)
		{
			add_history(input);
			exit_check(input);
			parse_input(input, envp);
		}
		free(input);
	}
	clear_history();
	return (0);
}
