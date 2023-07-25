/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:09:41 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/25 16:27:30 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static char	*fill_output(char *out, char *str, int i, int j)
{
	int	open;

	open = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			out[j++] = str[i];
		else if (open)
		{
			if ((open == 1 && str[i] != '\'') || (open == 2 && str[i] != '\"'))
				out[j++] = str[i];
			else
				open = 0;
		}
		else if (!open)
		{
			if (str[i] == '\'')
				open = 1;
			else if (!open && str[i] == '\"')
				open = 2;
		}
		i++;
	}
	out[j] = '\0';
	return (out);
}

char	*remove_quotes(char *str)
{
	char	*out;

	if (!ft_strchr(str, '\'') && !ft_strchr(str, '\"'))
		return (str);
	out = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!out)
		return (NULL);
	out = fill_output(out, str, 0, 0);
	return (out);
}
