/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:53:30 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/08 19:38:24 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include <stdlib.h>
#include <stdio.h>

static char	*allocate_new_redirects(char *str, int i, int *count)
{
	if (str[i] == '<' && str[i + 1] != '<' && str[i - 1] != '<')
	{
		*count = 1;
		return (" < ");
	}
	else if (str[i] == '<' && (str[i + 1] == '<' || str[i - 1] == '<'))
	{
		*count = 2;
		return (" << ");
	}
	else if (str[i] == '>' && str[i + 1] != '>' && str[i - 1] != '>')
	{
		*count = 1;
		return (" > ");
	}
	else if (str[i] == '>' && (str[i + 1] == '>' || str[i - 1] == '>'))
	{
		*count = 2;
		return (" >> ");
	}
	return (NULL);
}

static char	*allocate_new_input(char *out, char *str, int i)
{
	char	*aux;
	char	*remains;
	char	*fix;
	int		count;

	aux = out;
	count = 0;
	if (str[i] == '|')
	{
		fix = " | ";
		count = 1;
	}
	else
		fix = allocate_new_redirects(str, i, &count);
	if (str[i + count])
	{
		remains = str + i + count;
		remains = ft_strjoin(fix, remains);
		aux = ft_strjoin(aux, remains);
		free(remains);
	}
	else
		return (ft_strjoin(aux, fix));
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
	printf("OLD INPUT: %s\tSTR: %s\n", out, str);
	out = allocate_new_input(out, str, i);
	printf("NEW INPUT: %s\n", out);
	free(aux);
	if (!out)
		return (NULL);
	return (out);
}

static char	*first_pos_re(char *str)
{
	if (str[0] == '<' && str[1] != '<' && str[1] != ' ' && str[1])
		return (ft_strjoin("< ", (str + 1)));
	else if (str[0] == '<' && str[1] == '<' && str[2] != '<'
			&& str[2] != ' ' && str[2])
		return (ft_strjoin("<< ", (str + 2)));
	if (str[0] == '>' && str[1] != '>' && str[1] != ' ' && str[1])
		return (ft_strjoin("> ", (str + 1)));
	else if (str[0] == '>' && str[1] == '>' && str[2] != '>'
		&& str[2] != ' ' && str[2])
		return (ft_strjoin(">> ", (str + 2)));
	return (ft_strdup(str));
}

char	*clean_input(char *str)
{
	int		i;
	char	*tmp;
	char	*aux;

	tmp = first_pos_re(str); // If this is null syntax error near unexpected token 
	i = needs_space(tmp);
	printf("NEEDS SPACE IN POS: %d\n", i);
	while (i)
	{
		if (i < 0) // Error management
			return (NULL);
		else
		{
			aux = tmp;
			tmp = rewrite_input(tmp, i);
			if (!tmp)
				return (NULL); // mem error
			free(aux);
		}
		printf("REWRITTEN INPUT: %s\n", tmp);
		i = needs_space(tmp);
		printf("NEEDS SPACE IN POS: %d\n", i);
	}
	return (tmp);
}
