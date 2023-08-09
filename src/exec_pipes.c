/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:52:31 by laugarci          #+#    #+#             */
/*   Updated: 2023/08/09 13:02:19 by laugarci         ###   ########.fr       */
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

#define READ_END 0
#define WRITE_END 1

int	is_pipe(t_list *lst)
{
	t_token *aux;
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		aux = tmp->content;
		if (aux->type == PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	count_chars(t_list *lst)
{
	int	c;
	t_list *tmp;
	t_token *aux;

	c = 0;
	tmp = lst;
	while (tmp)
	{
		aux = tmp->content;
		if (aux->type == PIPE)
			c++;
		tmp = tmp->next;
	}
	return (c);
}

char	*find_command(t_list *lst, int i, int num_pipes)
{
	t_token *token;
	t_list *tmp;
	char *command;
	int j;
	int x;
	int aux;
	
	aux = 0;
	j = 0;
	tmp = lst;
	token = lst->content;
	command = malloc(sizeof(char) * 50);
	if (!command)
			return (NULL);
	printf("la i es %d\n", i);
//	if (i == 0)
//	{
		while(token->type == -1 && tmp->next)
		{
			if (aux > 0)
				command[j++] = ' ';
			x = 0;
			while (token->string[x])
				command[j++] = token->string[x++];
			aux++;
			tmp = tmp->next;
			token = tmp->content;
		}
//	}
/*	else
	{
		aux = 0;
		x = 0;
		j = 0;
		printf("i %d\n", i);
		while (x <= i)
		{

			tmp = tmp->next;
			token = tmp->content;
			x++;
		}
		if (token->type == PIPE)
		{
			tmp = tmp->next;
			token = tmp->content;
		}
		printf("token->string >> %s\n", token->string);
		while (tmp->next && token->type != PIPE)
		{
			x = 0;
			if (aux > 0)
				command[j++] = ' ';
			while(token->string[x])
				command[j++] = token->string[x++];
			printf("command >>  %s\n", command);
			tmp = tmp->next;
			token = tmp->content;
			aux++;
		}
	}*/
	num_pipes = 0; //quitar esto
	command[j] = '\0';
	printf("-------------------------------------\n");
	printf("COMANDO FINAL >> %s\n", command);
	printf("-------------------------------------\n");
	return (command);
}

void	exec_pipes(t_list *lst, char **env, int num_pipes)
{
	int		status;
	int		i;
	pid_t	pid;
	char	*command;
	int		**fds;
	t_list	*aux;

	i = 0;
	fds = malloc(sizeof(int *) * num_pipes);
	while (i <= num_pipes)
	{
		fds[i] = malloc(sizeof(int) * 2);
		pipe(fds[i]);
		i++;
	}
	i = 0;
	command = find_command(lst, i, num_pipes);
//	printf("command %d: %s\n", i, command);
	while (i <= num_pipes)
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
			parse_input(command, env, &aux);
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
		i++;
		command = find_command(lst, i, num_pipes);
//		printf("command %d: %s\n", i, command);
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
