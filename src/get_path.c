/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:31:29 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/05 14:04:54 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

// Debugging - Must delete later
#include <stdio.h>

static char	**join_path_cmd(char **path, char *cmd)
{
	int		i;
	char	*aux;

	i = 0;
	while (path[i])
	{
		aux = path[i];
		path[i] = ft_strjoin(path[i], "/");
		free(aux);
		if (!path[i])
			return (NULL);
		aux = path[i];
		path[i] = ft_strjoin(path[i], cmd);
		free(aux);
		if (!path[i])
			return (NULL);
		i++;
	}
	return (path);
}

static char	*get_right_path(char **path, char *cmd)
{
	int		i;
	char	*out;

	i = 0;
	out = NULL;
	while (path[i])
	{
		if (!access(path[i], F_OK))
		{
			out = ft_strdup(path[i]);
			if (access(path[i], X_OK))
				put_error(cmd, 128); // Error: Path has been found but it's not executable
			break ;
		}
		i++;
	}
	return (out);
}

static char	*get_path_util(char *str, char *cmd)
{
	char	**path;
	char	*out;

	str = ft_strtrim(str, "PATH=");
	path = ft_split(str, ':');
	free(str);
	if (!path)
		return (NULL);
	path = join_path_cmd(path, cmd);
	out = get_right_path(path, cmd);
	free_double((void **)path);
	return (out);
}

/* cmd is a command and it's arguments splitted by spaces since it's needed
 * by execve that the command and it's flags/arguments are in a char **
 * 
 * This function recieves a command and returns an allocated string containing 
 * it's path + command.
 * In order to do this, must check first if the command recieved already has 
 * it's path or needs to find it.
 * If it has it's path, it must return it.
 * If it doesn't, it appends all possible Paths with the command, in order
 * to check with access if the directory exists and it's executable, and 
 * returns the correct path. */
char	*get_path(char **cmd, char **envp)
{
	int		i;
	char	*aux;
	char	*out;

	if (cmd[0][0] == '/')
	{
		// Comprobar que el path existe y es ejecutable
		if (access(cmd[0], F_OK))
		{
			if (access(cmd[0], X_OK))
				put_error(cmd[0], 128);
		}
		else
			put_error(cmd[0], 127);
		return (ft_strdup(cmd[0]));
	}
	i = 0;
	while (envp[i])
	{
		aux = ft_strnstr(envp[i++], "PATH", 4);
		if (aux != NULL)
			break ;
	}
	if (!aux)
	{
		put_error(cmd[0], 127); // Error: command not found
		return (NULL);
	}
	out = get_path_util(aux, cmd[0]);
	if (!out)
		put_error(cmd[0], 127); // Error: command not found
	return (out);
}
