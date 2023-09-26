/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:31:29 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/26 13:02:27 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

static char	**join_path_cmd(char **path, char *cmd, int i)
{
	char	*aux;
	char	*tmp;

	while (path[++i])
	{
		aux = ft_strjoin(path[i], "/");
		if (!aux)
		{
			free_double((void **)path);
			return (NULL);
		}
		tmp = path[i];
		path[i] = aux;
		free(tmp);
		aux = ft_strjoin(path[i], cmd);
		if (!aux)
		{
			free_double((void **)path);
			return (NULL);
		}
		tmp = path[i];
		path[i] = aux;
		free(tmp);
	}
	return (path);
}

static int	get_right_path(char **path, char **dst)
{
	int		i;
	char	*out;

	i = 0;
	out = NULL;
	while (path[i])
	{
		if (!access(path[i], F_OK))
		{
			if (access(path[i], X_OK))
				return (128); // Permission denied
			else
			{
				*dst = ft_strdup(path[i]);
				if (!dst)
					return (12);
				return (0);
			}
		}
		i++;
	}
	return (127); // command not found
}

static int	get_path_util(char *str, char *cmd, char **dst)
{
	char	**path;
	char	**aux;
	int		err;

	str = ft_strtrim(str, "PATH=");
	if (!str)
		return (12);
	path = ft_split(str, ':');
	free(str);
	if (!path)
		return (12);
	aux = path;
	path = join_path_cmd(path, cmd, -1);
	if (!path)
		return (12);
	err = get_right_path(path, dst);
	free_double((void **)path);
	if (err)
		return (err);
	return (0);
}

static int	is_absolute_path(char *cmd)
{
	if (!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "../", 3 )
		|| cmd[0] == '/')
	{
		if (!access(cmd, F_OK))
		{
			if (access(cmd, X_OK))
				return (128); // Permission denied
		}
		else
			return (127); // No such file or directory
		return (1);
	}
	return (0);
}

int	get_path(char *cmd, char **envp, char **dst)
{
	int		i;
	int		err;
	char	*aux;
	
	err = is_absolute_path(cmd);
	if (err == 1)
	{
		*dst = ft_strdup(cmd);
		return (0);
	}
	else if (err)
		return (err);
	i = 0;
	aux = NULL;
	while (envp[i] && !aux)
		aux = ft_strnstr(envp[i++], "PATH", 4);
	if (!aux)
		return (127); // command not found
	return (get_path_util(aux, cmd, dst));
}
