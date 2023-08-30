/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:09:41 by ffornes-          #+#    #+#             */
/*   Updated: 2023/08/30 12:42:56 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

int	check_quote_state(char *input)
{
	int	i;
	int	state;

	i = 0;
	state = 0;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			if (!state)
				state = 1;
			else if (state == 1)
				state = 0;
		}
		else if (input[i] == '\"')
		{
			if (!state)
				state = 2;
			else if (state == 2)
				state = 0;
		}
		i++;
	}
	return (state);
}

static int	close_state(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	return (0);
}

static char	*fill_output(char *out, t_token *token, int i, int j)
{
	char	*str;
	int		open;

	open = 0;
	str = token->string;
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
			open = close_state(str[i]);
		i++;
	}
	out[j] = '\0';
	return (out);
}

t_token	*remove_quotes(t_token *token)
{
	char	*str;
	char	*out;

	str = token->string;
	if (!ft_strchr(str, '\'') && !ft_strchr(str, '\"'))
		return (token);
	out = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!out)
		return (NULL);
	out = fill_output(out, token, 0, 0);
	token->string = out;
	return (token);
}
