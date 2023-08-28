/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 18:22:49 by ffornes-          #+#    #+#             */
/*   Updated: 2023/08/28 11:58:43 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "minishell_defs.h"

#include <stdio.h>

static char	**realloc_envp(char *einval, t_data *data)
{
	int		i;
	char	**og_envp;
	char	**new_envp;

	i = 0;
	og_envp = data->envp;
	while (og_envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (og_envp[i])
	{
		new_envp[i] = og_envp[i];
		i++;
	}
	new_envp[i] = ft_strdup(einval);
	if (!new_envp[i++]) // Error: Not enough memory in strdup
	{
		free(new_envp);
		return (NULL);
	}
	new_envp[i] = NULL;
	return (new_envp);
}

static int	modify_einval(char *einval, char *envp[], size_t pos)
{
	if (envp[pos])
		free(envp[pos]);
	else
		return (1);
	envp[pos] = ft_strdup(einval);
	return (0);
}

int	builtin_export(char *einval, t_data *data)
{
	char	**og_envp;
	char	**new_envp;
	int		i;
	size_t	size;

	if (!ft_strchr(einval, '='))
		return (0);
	i = 0;
	og_envp = data->envp;
	size = ft_strlen(einval);
	while (og_envp[i])
	{
		if (!ft_strncmp(einval, og_envp[i], size))
		{
			modify_einval(einval, og_envp, i);
			return (0);
		}
		i++;
	}
	new_envp = realloc_envp(einval, data);
	if (!new_envp)
		return (1);
	free(data->envp);
	data->envp = new_envp;
	return (0);
}
