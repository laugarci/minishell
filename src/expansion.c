/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:47:53 by ffornes-          #+#    #+#             */
/*   Updated: 2023/08/29 14:15:56 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static char	*update_input_util(int i, char *tmp, char *str, char *input)
{
	char	*aux;

	aux = tmp;
	if (!str)
		str = "";
	tmp = ft_strjoin(tmp, str);
	if (!tmp)
		return (NULL);
	free(aux);
	aux = tmp;
	while (input[i] != ' ' && input[i])
		i++;
	if (input[i])
	{
		tmp = ft_strjoin(tmp, (input + i));
		free(aux);
		if (!tmp)
			return (NULL);
	}
	return (tmp);
}

static char	*update_input(char *input, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (input[i])
		if (input[i++] == '$' && (i - 1 == 0 || input[i - 2] == ' '))
			break ;
	tmp = malloc(sizeof(char) * i);
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, input, i);
	tmp = update_input_util(i, tmp, str, input);
	return (tmp);
}

static char	*expand_input(char *input, char *envp[])
{
	char	*str;
	char	*aux;
	int		i;

	str = ft_strchr(input, '$');
	if (!str)
		return (NULL);
	str++;
	aux = ft_strdup(str);
	if (!aux)
		return (NULL);
	i = 0;
	while (aux[i])
	{
		if (aux[i] == ' ')
		{
			aux[i] = '\0';
			break ;
		}
		i++;
	}
	str = find_eval(aux, envp);
	free(aux);
	return (str);
}

static char	*trunc_input(char *input, char *output)
{
	char	*out;
	int		i;

	i = 0;
	while (ft_isalnum(input[i]))
		i++;
	if (input[i] && input[i] != ' ') // This doesn't work yet lol
	{
		out = ft_strjoin(output, (input + i));
		free(input);
		free(output);
		return (out);
	}
	free(input);
	return (output);
}

char	*expand_evals(char *input, char *envp[])
{
	int		amount;
	char	*aux;
	char	*out;

	out = ft_strdup("");
	if (!out)
		return (NULL);
	amount = expansion_amount(input);
	if (!amount)
		return (input);
	while (amount--)
	{
		aux = input;
		free(out);
		out = expand_input(input, envp);
		out = update_input(input, out);
		input = ft_strdup(out);
		if (!input)
			return (NULL);
		free(aux);
	}
	return (trunc_input(input, out));
}
