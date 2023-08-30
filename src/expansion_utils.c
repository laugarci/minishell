/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:04:51 by ffornes-          #+#    #+#             */
/*   Updated: 2023/08/30 15:46:33 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*true_eval(char *str)
{
	int		i;
	char	*out;

	i = 0;
	while (str[i])
		if (str[i++] == '$')
			break ;
	if (str[i - 1] != '$')
		return (ft_strdup(str));
	out = malloc(sizeof(char) * i);
	if (!out)
		return (NULL);
	ft_strlcpy(out, str, i);
	return (out);
}

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
