/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:52:21 by laugarci          #+#    #+#             */
/*   Updated: 2023/06/30 15:15:23 by laugarci         ###   ########.fr       */
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
	
	if (argc > 1)
		exit(1);

	int	i = 0;
	while (argv[i])
		printf("%s\n", argv[i++]);

	while (1)
	{
		input = readline("minishell > ");
		if (input[0] != '\0' && input)
		{
			add_history(input);
			exit_check(input);
			parse_input(input, envp);
			ft_exec_commands(argc, argv);
		}
		free(input);
	}
	clear_history();
	return (0);
}
