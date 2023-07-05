/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:29:42 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/05 18:23:12 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

static int	save_input(char **dst, char *src)
{
	char	*out;
	int		i;

	i = 0;
	while (src[i] && src[i] != ' ')
		i++;
	dst = &out;
	out = malloc(sizeof(char *) * (i + 1));
	if (!out)
		return (1);
	out = ft_strlcpy(out, src, i + 1);
	return (0);
}

/*	This function gets the input from readline and splits it by spaces, in order
 *	to get all the different arguments recieved.
 *	
 *	*/
void	parse_input(char *str, char *envp[])
{
	char	**input;
	char	*aux;

	
	/*
	input = ft_split(str, ' ');
	if (input[0]) 
	{
		if (!ft_strncmp(input[0], "<<", 2))
		{
			printf("parse_heredoc(input)\n");
			here_doc(input, envp);
		}
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
	*/
}
