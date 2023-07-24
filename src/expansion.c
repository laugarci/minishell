/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:47:53 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/24 16:14:02 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static char	*update_input(char *input, char *str)
{
	int		i;
	char	*tmp;
	char	*aux;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && (i == 0 || input[i - 1] == ' '))
			break ;
		i++;
	}
	tmp = input;
	tmp[i] = '\0';
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
	char	*out;
	int		i;

	str = ft_strchr(input, '$');
	if (!str)
		return (NULL);
	str++;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			str[i] = '\0';
			break ;
		}
		i++;
	}
	str = find_eval(str, envp);
	out = update_input(input, str);
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
	while (j)
	{
		aux = input;
		out = expand_input(input, envp);
		input = ft_strdup(out);
		if (!input)
			return (NULL);
		free(aux);
		j--;
	}
	return (out);
}
