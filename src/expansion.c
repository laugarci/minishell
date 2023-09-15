/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:47:53 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/15 11:29:20 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static char	*expand_input_util(char *input)
{
	char	*str;

	str = ft_strchr(input, '$');
	if (!str)
		return (NULL);
	while (*(str + 1) == '$')
		str++;
	str++;
	while (*str && *str == ' ')
	{
		str = ft_strchr(str, '$');
		if (!str)
			return (NULL);
		str++;
	}
	return (str);
}

// This function locates the environment value in the string 
// 	recieved as input, trimming the environment value leaving 
// 	only it's reference name.
// 		Ex: ' nskj $USER a' becomes 'USER'
// Then find_eval is called, which looks for the environment 
// 	value in the environment and
// 		returns the content saved in the environment value.
static char	*expand_input(char *input, char *envp[], int *exit_status)
{
	char	*str;
	char	*aux;
	int		i;

	str = expand_input_util(input);
	if (!str)
		return (NULL);
	else if (*str == '?')
		return (ft_itoa(*exit_status));
	aux = ft_strdup(str);
	if (!aux)
		return (NULL);
	i = -1;
	while (aux[++i])
	{
		if (aux[i] == ' ')
		{
			aux[i] = '\0';
			break ;
		}
	}
	find_eval(aux, envp, &str);
	free(aux);
	return (ft_strdup(str));
}

char	*expand_evals(char *input, char *envp[], int *exit_status)
{
	int		amount;
	char	*aux;
	char	*out;

	amount = expansion_amount(input);
	if (!amount)
		return (input);
	out = ft_strdup("");
	if (!out)
		return (NULL);
	while (amount--)
	{
		aux = input;
		free(out);
		out = expand_input(input, envp, exit_status);
		if (out)
			out = update_input(input, out);
		if (!out)
			return (NULL);
		input = ft_strdup(out);
		free(aux);
	}
	free(out);
	return (input);
}
