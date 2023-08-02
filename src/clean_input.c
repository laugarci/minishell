/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:53:30 by ffornes-          #+#    #+#             */
/*   Updated: 2023/08/02 19:27:46 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include <stdlib.h>
#include <stdio.h>

static int	check_character(char *str, int i)
{
	if (str[i] == '|')
	{
		if ((i > 0 && str[i - 1] == '|') || str[i + 1] == '|')
			return (-1);
		if (i > 0 && str[i - 1] != ' ')
			return (i);
		else if (str[i + 1] != ' ')
			return (i);
	}
	else if (str[i] == '<' || str[i] == '>')
	{
		if (str[i] == '>' && str[i - 1] == '<')
			return (-2);
		if (i > 0 && str[i - 1] != ' ' && str[i - 1] != str[i])
			return (i);
	}
	return (0);
}

static int	needs_space(char *str)
{
	int	i;
	int	out;
	int	open;

	i = 0;
	out = 0;
	open = 0;
	while (str[i])
	{
		open = open_state(open, str[i]);
		if (!open)
			out = check_character(str, i);
		if (out != 0)
			return (out);
		i++;
	}
	return (0);
}

static char	*allocate_new_input(char **out, char *str, int i)
{
	char	*aux;

	aux = *out;
	if (str[i] == '|')
		aux = ft_strjoin(aux, " | ");
	else if (str[i] == '<')
		aux = ft_strjoin(aux, " <");
	else if (str[i] == '>')
		aux = ft_strjoin(aux, " >");
	return (aux);
}

static char	*rewrite_input(char *str, int i)
{
	char	*out;
	char	*aux;

	out = malloc(sizeof(char) * i + 1);
	if (!out)
		return (NULL);
	ft_strlcpy(out, str, i + 1);
	aux = out;
	out = allocate_new_input(&out, str, i);
	free(aux);
	if (!out)
		return (NULL);
	aux = out;
	out = ft_strjoin(out, (str + i + 1));
	free(aux);
	if (!out)
		return (NULL);
	return (out);
}

int	clean_input(char **str)
{
	int		i;
	char	*tmp;
	char	*aux;

	i = needs_space(*str);
	tmp = ft_strdup("");
	while (i)
	{
		if (i == -1) // Error management
			return (46);
		else if (i == -2) // Error management
			return (47);
		else
		{
			aux = tmp;
			tmp = rewrite_input(*str, i);
			if (!tmp)
				return (1); // mem error
			*str = tmp;
		}
		i = needs_space(tmp);
	}
	free(tmp);
	return (0);
}
