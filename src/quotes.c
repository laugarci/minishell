/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:09:41 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/04 17:48:51 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

int	quote_state(int state, char c)
{
	if (!state && c == '\'')
		return (1);
	else if (!state && c == '\"')
		return (2);
	else if ((state == 1 && c == '\'') || (state == 2 && c == '\"'))
		return (0);
	return (state);
}

static char	*fill_output(char *out, t_token *token, int i, int j)
{
	char	*str;
	int		open;

	open = 0;
	str = token->string;
	token->quotes = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			out[j++] = str[i];
		else if (open)
		{
			token->quotes = open;
			if ((open == 1 && str[i] != '\'') || (open == 2 && str[i] != '\"'))
				out[j++] = str[i];
			else
				open = 0;
		}
		else if (!open)
			open = quote_state(open, str[i]);
		i++;
	}
	out[j] = '\0';
	return (out);
}

t_token	*remove_quotes(t_token *token)
{
	char	*str;
	char	*out;
	char	*aux;

	str = token->string;
	if (!ft_strchr(str, '\'') && !ft_strchr(str, '\"'))
		return (token);
	out = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	if (!out)
		return (NULL);
	out = fill_output(out, token, 0, 0);
	aux = token->string;
	token->string = out;
	free(aux);
	return (token);
}
