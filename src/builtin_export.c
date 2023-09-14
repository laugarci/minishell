/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 18:22:49 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/14 12:02:51 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

#include <stdio.h>

static char	**realloc_envp(char *eval, char **envp)
{
	int		i;
	char	**og_envp;
	char	**new_envp;

	i = 0;
	og_envp = envp;
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
	new_envp[i] = ft_strdup(eval);
	if (!new_envp[i++]) // Error: Not enough memory in strdup
	{
		free(new_envp);
		return (NULL);
	}
	new_envp[i] = NULL;
	return (new_envp);
}

static int	modify_eval(char *eval, char *envp[], size_t pos)
{
	if (envp[pos])
		free(envp[pos]);
	else
		return (1);
	envp[pos] = ft_strdup(eval);
	return (0);
}

int	builtin_export(char *eval, char **envp)
{
	char	**og_envp;
	char	**new_envp;
	int		i;
	size_t	size;

	if (!ft_strchr(eval, '='))
		return (0);
	i = 0;
	og_envp = envp;
	size = ft_strlen(eval);
	while (og_envp[i])
	{
		if (!ft_strncmp(eval, og_envp[i], size))
		{
			modify_eval(eval, og_envp, i);
			return (0);
		}
		i++;
	}
	new_envp = realloc_envp(eval, envp);
	if (!new_envp)
		return (1);
	free_double((void **)envp);
	envp = new_envp;
	return (0);
}
