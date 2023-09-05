/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:47:53 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/05 13:12:00 by ffornes-         ###   ########.fr       */
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
	while (input[i] && ((!i && (ft_isalpha(input[i]) || input[i] == '_'))
			|| (ft_isalnum(input[i]) || input[i] == '_')))
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
		if (input[i++] == '$')
			if (ft_isalpha(input[i]) || input[i] == '_')
				break ;
	tmp = malloc(sizeof(char) * i);
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, input, i);
	tmp = update_input_util(i, tmp, str, input);
	return (tmp);
}

static char	*expand_input_util(char *input)
{
	char	*str;

	str = ft_strchr(input, '$');
	if (!str)
		return (NULL);
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
static char	*expand_input(char *input, char *envp[])
{
	char	*str;
	char	*aux;
	int		i;

	str = expand_input_util(input);
	if (!str)
		return (NULL);
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
	find_eval(aux, envp, &str); // Returns error code
	free(aux);
	return (str);
}

char	*expand_evals(char *input, char *envp[])
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
		out = expand_input(input, envp); // Unprotected malloc
		out = update_input(input, out); // Unprotected malloc
		input = ft_strdup(out);
		if (!input) // If out is allocated must free it before returning NULL
			return (NULL);
		free(aux);
	}
	free(out);
	return (input);
}
