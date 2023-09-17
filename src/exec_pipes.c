/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:52:31 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/17 16:11:59 by laugarci         ###   ########.fr       */
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

void	close_pipes_child(int **fds, int i, int num_pipes, t_list *lst)
{
	if (is_type(lst, 3) || is_type(lst, 4) || is_type(lst, 1))
	{
		if (check_redirect(lst))
			exec_redirect(lst);
	}
	if (i != 0)
	{
		close(fds[i - 1][WRITE_END]);
		if (!is_type(lst, 1))
			dup2(fds[i - 1][READ_END], STDIN_FILENO);
		close(fds[i - 1][READ_END]);	
	}	
	if (i != num_pipes)
	{
		close(fds[i][READ_END]);
		if (check_redirect(lst) == 0)
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

void	exec_pipes(char **env, int num_pipes, t_list *lst)
{
	int		i;
	pid_t	pid;
	int		**fds;
	int		check;
	t_list	*aux;

	check = 0;
	aux = lst;
	if (num_pipes)
		fds = pipe_fds(num_pipes);
	i = 0;
	while (i < (num_pipes + 1))
	{
		pid = fork();
		if (pid == -1)
			exit(-1);
		else if (pid == 0)
		{
			if (i == num_pipes)
			{
				if (is_type(aux, 2))
					here_doc(aux);
			}
			close_pipes_child(fds, i, num_pipes, lst);
			if (is_type(lst, 1))
				check = check_infile(lst);
			if (check == 0)
				exec_commands(lst, env);
			exit(1);
		}
		else
			close_pipes_parent(fds, i, num_pipes);
		lst = move_to_pipe(lst);
		i++;
	}
	close_pipes(fds, num_pipes);
}
