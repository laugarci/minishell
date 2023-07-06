/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:00:39 by laugarci          #+#    #+#             */
/*   Updated: 2023/07/06 17:43:43 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "libft.h"
#include "minishell.h"

/*
static int	child_process()
{

}
*/

int	exec_cd(char **input)
{

	if (access((input[1]), F_OK) != -1)
	{
		if (access(input[1], R_OK) == 0) //permisos de lectura
		{
			if (chdir(input[1]) == -1)
			{
				printf("minishell: cd: %s: No such file or directory\n", input[1]);
				return (1);
			}
		}
		else
		{
			printf("minishell: cd: %s: Permission denied\n", input[1]);
			return (1);
		}
	}
	else
	{
		printf("minishell: cd: %s: No such file or directory\n", input[1]);
		return (1);
	}
	return (0);
}

int	cmp_commands(char *input, char **env)
{
	char **commands;

	commands = ft_split(input, ' ');
	if (ft_strncmp(input, "cd ", 3) == 0)
		exec_cd(commands);
	else
		exec_commands(input, env);
	return (0);
}

int	exec_commands(char *input, char **env)
{
	char	*space_pos;
	char	*command;
	char	*flags;
	char	**args;
	int		status;
	char **test;
	pid_t	pid;
	
	test = ft_split(input, ' ');
	pid = fork();
	if (pid == 0)
	{
		space_pos = ft_strchr(input, ' ');
		if (space_pos != NULL)
		{
			command = (char *)malloc(sizeof(char) * ((space_pos - input) + 1));
			if (!command)
				return (1);
			flags = (char *)malloc(sizeof(char) * (ft_strlen(space_pos) + 2));
			if (!flags)
				return (1);
			ft_strlcpy(command, input, (space_pos - input) + 1);
			ft_strlcpy(flags, (space_pos + 1), (ft_strlen(space_pos + 1) + 1));
			args = (char **)malloc(3 * sizeof(char *));
			if (!args)
				return (1);
			args[0] = get_path(test, env);
			args[1] = flags;
			args[2] = NULL;
			execve(args[0], args, env);
			free(command);
			free(flags);
			free(args);
		}
		else
		{
			args = (char **)malloc(sizeof(char *) * 2);
			args[0] = get_path(test, env);
			args[1] = NULL;
			execve(args[0], args, env);
			free(args);
		}
	}
	else
		waitpid(pid, &status, 0);
	return (0);
}
