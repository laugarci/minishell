/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:29:42 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/27 14:43:35 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

/*	This function gets the input from readline and splits it by spaces, in order
 *	to get all the different arguments recieved.
 *	After splitting, it checks if the input has been saved correctly, this can fail
 *	when there is no more memory to allocate so split fails or when the line recieved
 *	is made of spaces exclusively. */
void	parse_input(char *str, char *envp[])
{
	char	**input;
	char	*aux;

	input = ft_split(str, ' ');
	free(str);
	if (input[0]) 
	{
		if (!ft_strncmp(input[0], "<<", 2))
			printf("parse_heredoc(input)\n");
		else
			printf("Treat as a command\n");
		aux = get_path(input, envp);
		if (aux)
		{
			printf("Path found: %s\n", aux);
			free(aux);
		}
	}
	free_double((void **)input);
}
