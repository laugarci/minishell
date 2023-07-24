/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:52:31 by laugarci          #+#    #+#             */
/*   Updated: 2023/07/24 12:18:32 by laugarci         ###   ########.fr       */
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

char	*ft_strtok(char *str, const char *del)
{
	static char	*token;
	char		*start;
	int			i;
	int			j;

	i = 0;
	if (str != NULL)
		token = str;
	if (token == NULL || *token == '\0')
		return (NULL);
	while (token[i] != '\0')
	{
		j = 0;
		while (del[j] != '\0')
		{
			if (token[i] == del[j])
			{
				i++;
				break ;
			}
			j++;
		}
		if (del[j] == '\0')
			break ;
	}
	if (token[i] == '\0')
		return (NULL);
	start = &token[i];
	while (token[i] != '\0')
	{
		j = 0;
		while (del[j] != '\0')
		{
			if (token[i] == del[j])
			{
				token[i] = '\0';
				i++;
				token += i;
				return (start);
			}
			j++;
		}
		i++;
	}
	token += i;
	return (start);
}

void	exec_command_pipes(char *command, char **env)
{
	char	**args;
	int		argindex;
	char	*token;

	args = malloc(sizeof(char *) * 3);
	argindex = 0;
	token = ft_strtok(command, " ");
	while (token != NULL)
	{
		args[argindex] = malloc(sizeof(char) * ft_strlen(token) + 1); //protect
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
	int		**fds;

	i = 0;
	fds = malloc(sizeof(int *) * num_pipes);
	while (i < num_pipes)
	{
		fds[i] = malloc(sizeof(int) * 2);
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
		command = ft_strtok(NULL, "|");
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