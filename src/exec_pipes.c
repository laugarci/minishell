/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:52:31 by laugarci          #+#    #+#             */
/*   Updated: 2023/08/16 17:00:40 by laugarci         ###   ########.fr       */
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

char	*find_command(t_list *lst)
{
	size_t	total_length;
	t_token	*token;
	t_list	*current;
	int		i;
	char	*result;

	i = 0;
	total_length = 0;
	current = lst;
	while (current->next)
	{
		token = current->content;
		total_length += ft_strlen(token->string);
		current = current->next;
		i++;
	}
	total_length = total_length + i;
	result = malloc(sizeof(char) * (total_length));
	current = lst;
	i = 0;
	while (current->next)
	{
		token = current->content;
		if (i > 0)
		{
			result[i] = ' ';
			i++;
		}
		ft_strlcpy(result + i, token->string, total_length);
		i += ft_strlen(token->string);
		current = current->next;
	}
	result[total_length] = '\0';
	return (result);
}

char	*find_output(t_list *lst)
{
	t_list *tmp;
	t_token *token;
	char *output;

	tmp = lst;
	token = tmp->content;
	while(tmp->next)
	{
		if (token->type == 3)
		{
			output = malloc(sizeof(char) * ft_strlen(token->string) + 1);
			ft_strlcpy(output, token->string, ft_strlen(token->string) + 1);
		}
		tmp = tmp->next;
		token = tmp->content;
	}
	return (output);
}

void	close_pipes(int **fds, int	num_pipes)
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
	int i;
	int **fds;

	i = 0;
	fds = malloc(sizeof(int *) * num_pipes);
	if (!fds)
		return (NULL);
	while (i < num_pipes)
	{
		fds[i] = malloc(sizeof(int) * 2);
		pipe(fds[i]);
		i++;
	}
	return (fds);
}

void	exec_pipes(t_list *lst, char **env, int num_pipes)
{
	int		i;
	pid_t	pid;
	char	*command;
	int		**fds;
	t_list	*aux;

	fds = pipe_fds(num_pipes);
	command = find_command(lst);
	command = ft_strtok(command, "|");
	i = 0;
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
			if (is_type(lst, 3) == 1)
				exec_redirect(lst);
			if (i != num_pipes)
			{
				close(fds[i][READ_END]);
				dup2(fds[i][WRITE_END], STDOUT_FILENO);
				close(fds[i][WRITE_END]);
			}
			aux = save_tokens(command);
			exec_commands(aux, env);
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
	close_pipes(fds, num_pipes);
}
