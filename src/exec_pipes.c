/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:52:31 by laugarci          #+#    #+#             */
/*   Updated: 2023/07/18 14:04:51 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "minishell.h"
#include "libft.h"

#define READ_END 0
#define WRITE_END 1

int is_pipe(char *input)
{
	if (ft_strchr(input, '|') != NULL)
        return (1);
	else
		return (0);
}

int	count_pipes(char *input)
{
	int i;
	int pipe;

	pipe = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
			pipe++;
		i++;
	}
	return (pipe);
}

void exec_pipes(char *input, char **env)
{
	int num_pipes;
	int fds[count_pipes(input)][2];
	int status;
	int i;
	pid_t pid;
	char	*command;
	env = NULL; //QUITAR
	
	num_pipes = count_pipes(input);
	i = 0;
	while (i < num_pipes)
	{
		pipe(fds[i]);
		i++;
	}
	i = 0;
	command = strtok(input, "|");
	while (command != NULL)
	{
		pid = fork();
		if (pid == -1)
			exit(-1);
		else if (pid == 0)
		{
			if (i != 0)
			{
				close(fds[i - 1][WRITE_END]);
				dup2(fds[i - 1][READ_END], STDIN_FILENO);
				close(fds[i - 1][READ_END]);
			}
			if (i != num_pipes)
			{
				close(fds[i][READ_END]);
				dup2(fds[i][WRITE_END], STDOUT_FILENO);
				close(fds[i][WRITE_END]);
			}
			char *args[64];
			int argIndex = 0;
			char *token = strtok(command, " ");
			while (token != NULL)
			{
				args[argIndex++] = token;
				token = strtok(NULL, " ");
			}
			args[argIndex] = NULL;
			execvp(args[0], args);
			exit(0);
		}
		else
		{
			if (i != 0)
				close(fds[i - 1][READ_END]);
			if (i != num_pipes)
				close(fds[i][WRITE_END]);
		}
		command = strtok(NULL, "|");
		i++;
	}
	i = 0;
	while (i < num_pipes)
	{
		close(fds[i][READ_END]);
		close(fds[i][WRITE_END]);
		i++;
	}
	i = 0;
	while (i <= num_pipes)
	{
		wait(&status);
		i++;
	}
}
