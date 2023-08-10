/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:53:30 by ffornes-          #+#    #+#             */
/*   Updated: 2023/08/10 13:47:04 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include <stdlib.h>
#include <stdio.h>

static char	*allocate_new_input(char *out, char *str, int i)
{
	char	*aux;

	aux = out;
	if (str[i] == '|')
		aux = ft_strjoin(aux, " | ");
	else if (str[i] == '<' && str[i + 1] != '<' && str[i - 1] != '<')
		aux = ft_strjoin(aux, " < ");
	else if (str[i] == '<' && (str[i + 1] == '<' || str[i - 1] == '<'))
	{
		if (aux[i - 1] == '<')
			aux[i - 1] = '\0';
		aux = ft_strjoin(aux, " << ");
	}
	else if (str[i] == '>' && str[i + 1] != '>' && str[i - 1] != '>')
		aux = ft_strjoin(aux, " > ");
	else if (str[i] == '>' && (str[i + 1] == '>' || str[i - 1] == '>'))
	{
		if (aux[i - 1] == '>')
			aux[i - 1] = '\0';
		aux = ft_strjoin(aux, " >> ");
	}
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
	out = allocate_new_input(out, str, i);
	free(aux);
	if (!out)
		return (NULL);
	aux = out;
	if (str[i + 1] != '<' && str[i + 1] != '>')
		out = ft_strjoin(out, (str + i + 1));
	else
		out = ft_strjoin(out, (str + i + 2));
	free(aux);
	if (!out)
		return (NULL);
	return (out);
}

static char	*first_pos_re(char *str)
{
	if (str[0] == '<' && str[1] != '<' && str[1] != '>' && str[1] != ' ')
		return (ft_strjoin("< ", (str + 1)));
	else if (str[0] == '<' && str[1] == '<' && str[2] != '<' && str[2] != '>' && str[2] != ' ') 
		return (ft_strjoin("<< ", (str + 2)));
	if (str[0] == '>' && str[1] != '<' && str[1] != '>' && str[1] != ' ')
		return (ft_strjoin("> ", (str + 1)));
	else if (str[0] == '>' && str[1] == '>' && str[2] != '<' && str[2] != '>' && str[2] != ' ')
		return (ft_strjoin(">> ", (str + 2)));
	return (NULL);
}

char	*clean_input(char *str)
{
	int		i;
	char	*tmp;
	char	*aux;
	
	if (str[0] == '<' || str[0] == '>')
		tmp = first_pos_re(str); // If this is null syntax error near unexpected token 
	else
		tmp = ft_strdup(str);
	i = needs_space(tmp);
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
		i = needs_space(tmp);
	}
	return (tmp);
}
