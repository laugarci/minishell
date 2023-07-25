/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:00:39 by laugarci          #+#    #+#             */
/*   Updated: 2023/07/25 10:33:36 by laugarci         ###   ########.fr       */
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
	if (access((input[1]), F_OK) != -1)
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

int	is_pipe(char *input)
{
	if (ft_strchr(input, '|') != NULL)
		return (1);
	else
		return (0);
}

int	cmp_commands(char *input, char **env)
{
	char	**commands;
	int		num_pipes;

	commands = ft_split(input, ' ');
	if (ft_strncmp(input, "cd ", 3) == 0)
		exec_cd(commands);
	else if (is_pipe(input) == 1)
	{
		num_pipes = count_chars(input, '|');
		exec_pipes(input, env, num_pipes);
	}
	else
		exec_commands(input, env);
	return (0);
}
/*
char	*ft_spaces(char *input)
{
	int i;
	char *str;
	int j;

	j = 0;
	i = 0;
	if (input[0] == ' ')
	{
		while(input[i] == ' ')
			i++;
	}
	else
		return(input);
	str = malloc(sizeof(char) * (ft_strlen(input) - i) + 1);
	i = 0;
	while(input[i] == ' ')
		i++;
	while(input[i])
		str[j++] = input[i++];
	return (str);
}*/

int	exec_commands_wf(char *space_pos, char *input, char **env)
{
	char	*command;
	char	**flags;
	char	**args;
	char	**split_command;
	int		count_flags;
	int		i;
	
	i = 0;
	count_flags = count_chars(input, '-');
	split_command = ft_split(input, ' ');
	command = (char *)malloc(sizeof(char) * ((space_pos - input) + 1));
	if (!command)
		return (1);
	flags = ft_split(space_pos + 1, ' ');
	if (!flags)
		return (1);
	args = (char **)malloc(sizeof(char *) * (count_flags + 2));
	if (!args)
		return (1);
	ft_strlcpy(command, input, (space_pos - input) + 1);
	args[0] = get_path(split_command, env);
	i = 0;
	while (i < count_flags)
	{
		args[i + 1] = flags[i];
		i++;
	}
	args[count_flags + 1] = NULL;
	execve(args[0], args, env);
	free(command);
	free(flags);
	free(args);
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
		{
			exec_commands_wf(space_pos, input, env);
			exit(0);
		}
		else
		{
			args = (char **)malloc(sizeof(char *) * 2);
			args[0] = get_path(split_command, env);
			args[1] = NULL;
			execve(args[0], args, env);
			free(args);
			exit(0);
		}
	}
	else
		waitpid(pid, &status, 0);
	return (0);
}
