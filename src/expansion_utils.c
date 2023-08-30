/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:04:51 by ffornes-          #+#    #+#             */
/*   Updated: 2023/08/30 16:11:20 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

// Trims the recieved input in order to return only the name of the einval 
// 		without any other stuff next to it.
// Useful in cases where two einvals are next to each other or other stuff is.
// 		ex:	$USER$USER     $USER.hola
static char	*true_eval(char *str)
{
	int		i;
	char	*out;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' || (!ft_isalnum(str[i]) && str[i] != '_'))
			break ;
		i++;
	}
	if (!str[i])
		return (ft_strdup(str));
	out = malloc(sizeof(char) * (i + 1));
	if (!out)
		return (NULL);
	ft_strlcpy(out, str, (i + 1));
	return (out);
}

// Finds in the environment recieved, the value of the einval 'str' and returns
// 		it.
char	*find_eval(char *str, char *envp[])
{
	int		i;
	int		j;
	char	*out;

	i = 0;
	str = true_eval(str);
	j = ft_strlen(str);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], str, ft_strlen(str)))
			if (envp[i][j] == '=')
				break ;
		i++;
	}
	if (envp[i])
	{
		out = ft_strchr(envp[i], '=');
		out++;
		free(str);
		return (out);
	}
	free(str);
	return (NULL);
}

// Returns the amount of expansions found in a string
int	expansion_amount(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '$' && ft_isalnum(input[i + 1]))
			j++;
		i++;
	}
	return (j);
}
