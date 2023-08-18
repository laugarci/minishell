/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:52:31 by laugarci          #+#    #+#             */
/*   Updated: 2023/08/18 14:50:42 by laugarci         ###   ########.fr       */
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
#include "parser.h"
#include "libft_bonus.h"
#include <fcntl.h>

#define READ_END 0
#define WRITE_END 1

void	close_pipes(int **fds, int num_pipes)
{
	int	i;
	int	status;

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

int	**pipe_fds(int num_pipes)
{
	int	i;
	int	**fds;

	i = 0;
	fds = malloc(sizeof(int *) * num_pipes);
	if (!fds)
		return (NULL);
	while (i < num_pipes)
	{
		fds[i] = malloc(sizeof(int) * 2);
		if (!fds[i])
			return (NULL);
		pipe(fds[i]);
		i++;
	}
	return (fds);
}

void	close_pipes_child(int **fds, int i, int num_pipes)
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
}

void	close_pipes_parent(int **fds, int i, int num_pipes)
{
	if (i != 0)
		close(fds[i - 1][READ_END]);
	if (i != num_pipes)
		close(fds[i][WRITE_END]);
}

void	exec_pipes(char **env, int num_pipes, char *command, t_list *lst)
{
	int		i;
	pid_t	pid;
	int		**fds;
	t_list	*aux;

	fds = pipe_fds(num_pipes);
	command = ft_strtok(command, "|");
	i = 0;

	while (command != NULL)
	{
		pid = fork();
		if (pid == -1)
			exit(-1);
		else if (pid == 0)
		{
			close_pipes_child(fds, i, num_pipes);
			if (is_type(lst, 3) == 1)
			{
				char *output = find_output(lst);
				int fd = open(output, O_WRONLY | O_CREAT | O_APPEND, 0666);
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
			aux = save_tokens(command);
			exec_commands(aux, env);
			exit(1);
		}
		else
			close_pipes_parent(fds, i, num_pipes);
		command = ft_strtok(NULL, "|");
		i++;
	}
	close_pipes(fds, num_pipes);
}
