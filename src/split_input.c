/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:35:07 by ffornes-          #+#    #+#             */
/*   Updated: 2023/08/09 14:11:36 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static char	*save_it(char *input, int start, int end)
{
	char	*out;

	out = malloc(sizeof(char) * (end + 1));
	if (!out)
		return (NULL);
	if (start)
		input += start;
	ft_strlcpy(out, input, end + 1);
	return (out);
}

static char	*get_string(char *input, int number, int i, int j)
{
	int		open;
	int		counted;
	int		count;

	open = 0;
	counted = 0;
	count = 0;
	while (input[++i])
	{
		open = open_state(open, input[i]);
		if (!open && input[i] == ' ')
			counted = 0;
		else
		{
			if (!counted)
				count++;
			if (count == number)
				j++;
			counted = 1;
		}
		if ((count != number && j) 
			|| (count == number && !open && input[i] == ' ' && j))
			break ;
	}
	return (save_it(input, (i - j), j));
}

static char	**save_new_input(char *input, int amount)
{
	char	**out;
	int		i;

	out = malloc(sizeof(char *) * (amount + 1));
	if (!out)
		return (NULL);
	i = 0;
	while (i < amount)
	{
		out[i] = get_string(input, (i + 1), -1, 0);
		if (!out)
		{
			free_double((void **)out);
			return (NULL);
		}
		i++;
	}
	out[i] = NULL;
	return (out);
}

static char	**charp_to_charpp(char *input)
{
	char	**out;

	out = malloc(sizeof(char *) * 2);
	if (!out)
		return (NULL);
	out[0] = ft_strdup(input);
	out[1] = NULL;
	return (out);
}

char	**split_input(char *input)
{
	int		i;
	int		j;
	int		open;
	int		counted;

	i = 0;
	j = 0;
	open = 0;
	counted = 0;
	while (input[i])
	{
		open = open_state(open, input[i]);
		if (!open && input[i] == ' ')
			counted = 0;
		else
		{
			if (!counted)
				j++;
			counted = 1;
		}
		i++;
	}
	if (j == 1)
		return (charp_to_charpp(input));
	return (save_new_input(input, j));
}
