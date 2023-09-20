/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:45:08 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/20 18:46:54 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_defs.h"
#include <stdlib.h>

t_env	*new_env_var(char *str)
{
	t_env	*var;

	var = malloc(sizeof(t_env));
	if (!var)
		return (NULL);
	var->key = ft_strdup(key);
	if (!var->key)
	{
		free(var);
		return (NULL);
	}
	if (value)
	{
		var->value = ft_strjoin("=", value);
		if (!var->value)
		{
			free(var);
			return (NULL);
		}
	}
	else
		var->value = NULL;
	return (var);
}
