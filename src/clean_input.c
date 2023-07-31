/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:53:30 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/31 12:38:59 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include <stdlib.h>
#include <stdio.h>

static int	open_state(int state, char c)
{
	if (!state && c == '\'')
		return (1);
	else if (!state && c == '\"')
		return (2);
	else if ((state == 1 && c == '\'') || (state == 2 && c == '\"'))
		return (0);
	return (state);
}

static int	needs_space(char *str)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (str[i])
	{
		open = open_state(open, str[i]);
		if (!open && str[i] == '|')
		{
			if ((i > 0 && str[i - 1] == '|') || str[i + 1] == '|')
				return (-1);
			if (i > 0 && str[i - 1] != ' ')
				return (i);
			else if (str[i + 1] != ' ')
				return (i);
		}
		i++;
	}
	return (0);
}

static char	*rewrite_input(char *str, int i)
{
	char	*out;
	char	*aux;

	out = malloc(sizeof(char) * i);
	if (!out)
	{
		free(str);
		return (NULL);
	}
	ft_strlcpy(out, str, i);
	aux = out;
	out = ft_strjoin(out, " | ");
	free(aux);
	if (!out)
		return (NULL);
	aux = out;
	out = ft_strjoin(out, (str + i));
	free(aux);
	if (!out)
		return (NULL);
	return (out);
}

int	clean_input(char **input)
{
	int		i;
	char	*aux;
	char	*str;

	str = *input;
	if (!ft_strchr(str, '|'))
		return (0);
	i = needs_space(str);
	while (i)
	{
		if (i < 0)
			return (46);
		else if (i)
		{
			aux = str;
			printf("Before: %s\n", str);
			str = rewrite_input(str, i + 1);
			printf("After: %s\n", str);
			if (!str)
				return (1); // mem error
			*input = str;
		}
		i = needs_space(str);
	}
	return (0);
}
