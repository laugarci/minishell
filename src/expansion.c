/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:47:53 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/24 16:42:32 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static char	*update_input(char *input, char *str)
{
	int		i;
	char	*tmp;
	char	*aux;

	i = 0;
	while (input[i])
		if (input[i++] == '$' && (i - 1 == 0 || input[i - 2] == ' '))
			break ;
	tmp = input;
	tmp[i - 1] = '\0';
	if (!str)
		str = "";
	tmp = ft_strjoin(tmp, str);
	if (!tmp)
		return (NULL);
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

static char	*find_eval(char *str, char *envp[])
{
	int		i;
	char	*out;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], str, ft_strlen(str)))
			break ;
		i++;
	}
	if (envp[i])
	{
		out = ft_strchr(envp[i], '=');
		out++;
		return (out);
	}
	return (NULL);
}

static char	*expand_input(char *input, char *envp[])
{
	char	*str;
	char	*aux;
	char	*out;
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
	out = update_input(input, str);
	free(aux);
	return (out);
}

char	*expand_evals(char *input, char *envp[])
{
	int		i;
	int		j;
	char	*out;
	char	*aux;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '$' && (i == 0 || input[i - 1] == ' '))
			j++;
		i++;
	}
	while (j--)
	{
		aux = input;
		out = expand_input(input, envp);
		input = ft_strdup(out);
		if (!input)
			return (NULL);
		free(aux);
	}
	return (out);
}
