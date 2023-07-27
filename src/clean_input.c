/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:53:30 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/27 17:03:36 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include <stdlib.h>

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

	out = malloc(sizeof(char) * i);
	if (!out)
	{
		free(str);
		return (NULL);
	}
	ft_strlcpy(out, str, i);
	free(str);
	return (out);
}

int	clean_input(char **input)
{
	int		i;
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
			str = rewrite_input(str, i);
			if (!str)
				return (1); // mem error
		}
		i = needs_space(str);
	}
	return (0);
}
