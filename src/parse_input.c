/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:29:42 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/06 13:05:43 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "parser.h"

static size_t	token_amount(char *input)
{
	size_t	i;
	size_t	j;

	if (!*input)
		return (0);
	i = 0;
	j = 1;
	while (input[i])
	{
		if (input[i] == '|')
			j++;
		if (input[i - 1] == '|')
			j++;
		i++;
	}
	return (j);
}

static char	*save_token(char *str)
{
	int		i;
	size_t	size;
	char	*aux;

	i = 0;
	if (str[i] == '|')
		size = 2;
	else
	{
		while (str[i] && str[i] != '|')
			i++;
		size = i + 1;
	}
	aux = malloc(sizeof(char) * size);
	if (!aux)
		return (NULL);
	ft_strlcpy(aux, str, size);
	return (aux);
}

static int	get_tokens(char **dst, char *input, size_t token_count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < (int)token_count)
	{
		dst[j] = save_token(input);
		if (!dst[j])
			return (1); // mem error in save_token
		if (*input == '|')
			input++;
		else
			while (*input && *input != '|')
				input++;
		j++;
	}
	dst[j] = NULL;
	return (0);
}

int	parse_input(char *str, char *envp[])
{
	char	**tokens;
	size_t	token_count;

	token_count = token_amount(str);
	if (!token_count)
		return (2); // No tokens found??
	tokens = malloc(sizeof(char *) * (token_count + 1));
	if (!tokens)
		return (1); // mem error
	if (get_tokens(tokens, str, token_count))
	{
		free_double((void **)tokens);
		return (1); // mem error in save_token
	}
	int	i = 0;
	while (tokens[i])
	{
		printf("Token %d: %s\n", i, tokens[i]);
		i++;
	}
	free_double((void **)tokens);
	return (0);

	envp[0] = NULL;
}
