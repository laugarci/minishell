/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:04:51 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/25 16:18:39 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*find_eval(char *str, char *envp[])
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

int	expansion_amount(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '$' 
			&& (i == 0 || input[i - 1] == ' ' || input[i - 1] == '\"'))
			j++;
		i++;
	}
	return (j);
}
