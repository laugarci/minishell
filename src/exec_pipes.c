/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:52:31 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/20 20:24:46 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "minishell.h"
#include "minishell_defs.h"
#include "libft.h"
#include "parser.h"
#include "libft_bonus.h"
#include <fcntl.h>

#define READ_END 0
#define WRITE_END 1

int	**close_pipes(int **fds, int num_pipes)
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
	return (fds);
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

int	close_pipes_child(int **fds, int i, int num_pipes, t_list *lst)
{
	if ((is_type(lst, 3) || is_type(lst, 4) || is_type(lst, 1)))
	{
		if (check_redirect(lst))
			exec_redirect(lst, 0);
	}
	if (i != 0)
	{
		close(fds[i - 1][WRITE_END]);
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
	return (0);
}

int	close_pipes_parent(int **fds, int i, int num_pipes)
{
	int	err;

	err = 0;
	if (i != 0)
		err = close(fds[i - 1][READ_END]);
	if (i != num_pipes)
		err = close(fds[i][WRITE_END]);
	return (check_error(err));
}

int	process_is_type(t_list *lst, int type)
{
	t_token	*aux;
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		aux = tmp->content;
		if (aux->type == PIPE)
			break ;
		if (aux->type == type)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}


int	exec_pipes(char **env, int num_pipes, t_list *lst)
{
	int		i;
	pid_t	pid;
	int		**fds;
	int		check;
	int		flag;
	t_list	*aux;

	aux = lst;
	flag = 0;
	check = 0;
	if (num_pipes)
	{
		fds = pipe_fds(num_pipes);
		if (fds == NULL)
			return (check_error(1));
	}
	i = 0;
	while (i < (num_pipes + 1))
	{
		pid = fork();
		if (pid == -1)
			exit(-1);
		else if (pid == 0)
		{	
			if (is_type(aux, 2) && i == num_pipes)
				here_doc(aux);
		//	set_or_return_state(MODE_SET, STATE_EXEC);
		//	signal_handler();
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
	fds = close_pipes(fds, num_pipes);
//	free_double((void **)fds); //este free crea muchos problemas
	return (0);
}
