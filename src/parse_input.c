/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:29:42 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/27 09:50:54 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "parser.h"

static size_t	get_input_amount(char *input)
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
		{
			if (input[i + 1] == '|')
			{
				input[i + 1] = '\0';
				return (j);
			}
			j++;
		}
		if (input[i - 1] == '|')
			j++;
		i++;
	}
	return (j);
}

static char	*save_input(char *str)
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

static int	get_inputs(char **dst, char *input, size_t token_count)
{
	int	j;

	j = 0;
	while (j < (int)token_count)
	{
		dst[j] = save_input(input);
		if (!dst[j])
			return (1); // mem error in save_input
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

static int	check_invalid_chars(char *input)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			j++;
		else if (input[i] == '\"')
			k++;
		else if (input[i] == '\\')
			return (42);
		else if (input[i] == ';')
			return (43);
		else if (input[i] == '>' && input[i + 1] == '<')
			return (258);
		i++;
	}
	if (j % 2 != 0 || k % 2 != 0)
		return (44);
	return (0);
}

int	parse_input(char *str, char *envp[])
{
	char	**inputs;
	size_t	input_count;
	int		error_id;

	error_id = check_invalid_chars(str);
	if (error_id)
		return (error_id);
	input_count = get_input_amount(str);
	if (!input_count)
		return (2); // No tokens found??
	inputs = malloc(sizeof(char *) * (input_count + 1));
	if (!inputs)
		return (1); // mem error
	if (get_inputs(inputs, str, input_count))
	{
		free_double((void **)inputs);
		return (1); // mem error in save_token
	}
//	return (0);

	free_double((void **)inputs);
	return (0);
	envp[0] = NULL;
}
