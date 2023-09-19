/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:11:02 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/19 17:43:53 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_defs.h"
#include <stdlib.h>

static unsigned int	env_size(char **envp)
{
	unsigned int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

static char	**set_env(char **envp, unsigned int size)
{
	char	**dst;
	int		i;

	dst = malloc(sizeof(char *) * (size + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		dst[i] = ft_strdup(envp[i]);
		if (!dst[i++])
		{
			free_double((void **)dst);
			return (NULL);
		}
	}
	dst[i] = NULL;
	return (dst);
}

int	init_data(t_data *data, char **envp)
{
	unsigned int	size;

	size = env_size(envp);
	data->env = set_env(envp, size);
	if (!data->env)
		return (12);
	return (0);
	data = NULL;
}
