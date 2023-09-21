/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:45:08 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/21 13:05:47 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "minishell_defs.h"
#include <stdlib.h>
#include <stdio.h>

static void	*free_and_return_envar(t_env *var)
{
	free_var(var);
	return (NULL);
}

t_env	*new_env_var(char *input)
{
	int		i;
	t_env	*out;

	i = 0;
	out = malloc(sizeof(t_env));
	if (!out)
		return (NULL);
	while (input[i] && input[i] != '=')
		i++;
	out->key = malloc(sizeof(char) * i + 1);
	if (!out->key)
		return (free_and_return_envar(out));
	ft_strlcpy(out->key, input, i + 1);
	input += i;
	if (input)
	{
		out->value = malloc(sizeof(char) * ft_strlen(input) + 1);
		if (!out->value)
			return (free_and_return_envar(out));
		ft_strlcpy(out->value, input, ft_strlen(input) + 1);
	}
	else
		out->value = NULL;
	return (out);
}
