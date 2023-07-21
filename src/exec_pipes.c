/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:52:31 by laugarci          #+#    #+#             */
/*   Updated: 2023/07/19 16:44:44 by laugarci         ###   ########.fr       */
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

int	is_pipe(char *input)
{
	if (ft_strchr(input, '|') != NULL)
		return (1);
	else
		return (0);
}

int	count_pipes(char *input)
{
	int	i;
	int	pipe;

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
char *ft_strtok(char *str, const char *del)
{
	static char *nextToken;
	char *start;
	int i;
	int j;
	
	i = 0;
	if (str != NULL)
		nextToken = str;
	if (nextToken == NULL || *nextToken == '\0')
		return (NULL);
	while (nextToken[i] != '\0')
	{
		j = 0;
		while (del[j] != '\0')
		{
			if (nextToken[i] == del[j])
			{
				i++;
				break ;
			}
			j++;
		}
		if (del[j] == '\0')
			break ;
	}
	if (nextToken[i] == '\0')
		return (NULL);
	start = &nextToken[i];
	while (nextToken[i] != '\0')
	{
		j = 0;
		while (del[j] != '\0')
		{
			if (nextToken[i] == del[j])
			{
				nextToken[i] = '\0';
				i++;
				nextToken += i;
				return (start);
			}
			j++;
		}
		i++;
	}
	nextToken += i;
	return (start);
}

void	exec_command_pipes(char *command, char **env)
{
	char	**args;
	int		argindex;
	char	*token;

	args = malloc(sizeof(char *) * 3);
	argindex = 0;
	token = ft_strtok(command, " "); //cambiar
	while (token != NULL)
	{
		args[argindex] = malloc(sizeof(char) * ft_strlen(token) + 1); //protect malloc
		ft_strlcpy(args[argindex], token, ft_strlen(token) + 1);
		argindex++;
		token = ft_strtok(NULL, " ");
	}
	args[argindex] = NULL;
	execve(get_path(args, env), args, env);
}

void	exec_pipes(char *input, char **env, int num_pipes)
{
	int		status;
	int		i;
	pid_t	pid;
	char	*command;
	int		fds[num_pipes][2]; //esto no se puede hacer

	i = 0;
	while (i < num_pipes)
	{
		pipe(fds[i]);
		i++;
	}
	i = 0;
	command = ft_strtok(input, "|");
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
			exec_command_pipes(command, env);
			exit(1);
		}
		else
		{
			if (i != 0)
				close(fds[i - 1][READ_END]);
			if (i != num_pipes)
				close(fds[i][WRITE_END]);
		}
		command = ft_strtok(NULL, "|"); //cambiar
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
