/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:00:39 by laugarci          #+#    #+#             */
/*   Updated: 2023/07/25 18:48:09 by laugarci         ###   ########.fr       */
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

int	exec_cd(char **input)
{
	if (input[1] == NULL)
	{
		if (chdir(getenv("HOME")) == 1)
			return (1);
	}
	else if (access((input[1]), F_OK) != -1)
	{
		if (access(input[1], R_OK) == 0)
		{
			if (chdir(input[1]) == -1)
			{
				printf("minishell: cd: %s", input[1]);
				printf(": No such file or directory\n");
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
	char	**commands;
	int		num_pipes;

	commands = ft_split(input, ' ');
	if (ft_strncmp(input, "cd ", 3) == 0 || ft_strncmp(input, "cd\0", 3) == 0)
		exec_cd(commands);
	else if (is_pipe(input) == 1)
	{
		num_pipes = count_chars(input, '|');
		exec_pipes(input, env, num_pipes);
	}
	else
		exec_commands(input, env);
	free_double((void **)commands);
	return (0);
}

int	exec_commands_wf(char *space_pos, char *input, char **env, char **split_com)
{
	int		i;
	char	**flags;
	char	**args;
	int		count_flags;

	count_flags = count_chars(input, '-');
	flags = ft_split(space_pos, ' ');
	args = (char **)malloc(sizeof(char *) * (count_flags + 3));
	if (!args)
		return (1);
	args[0] = get_path(split_com, env);
	i = 0;
	while (i <= count_flags)
	{
		args[i + 1] = flags[i];
		i++;
	}
	if (count_flags == 0)
		args[2] = NULL;
	else
		args[count_flags + 1] = NULL;
	execve(args[0], args, env);
	free_double((void **)flags);
	free_double((void **)args);
	return (0);
}

int	exec_commands(char *input, char **env)
{
	char	*space_pos;
	char	**args;
	int		status;
	char	**split_command;
	pid_t	pid;

	input = ft_strtrim(input, " ");
	split_command = ft_split(input, ' ');
	pid = fork();
	if (pid == 0)
	{
		space_pos = ft_strchr(input, ' ');
		if (space_pos != NULL)
			exec_commands_wf(space_pos, input, env, split_command);
		else
		{
			args = (char **)malloc(sizeof(char *) * 2);
			if (!args)
				return (1);
			args[0] = get_path(split_command, env);
			args[1] = NULL;
			execve(args[0], args, env);
			free_double((void **)args);
		}
		free((void **)split_command);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
	return (0);
}
