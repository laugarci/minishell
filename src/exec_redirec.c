/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:07:29 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/20 19:23:02 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft_bonus.h"
#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

int	check_infile(t_list *lst)
{
	char	*infile;

	infile = find_input(lst);
	if (access(infile, F_OK) == 0)
		return (0);
	else
		return (1); // Error: No such file or directory
}

t_list	*move_to_pipe(t_list *lst)
{
	t_token	*token;
	t_list	*aux;

	aux = lst;
	token = lst->content;
	while (token->type != PIPE)
	{
		if (!lst->next)
			break ;
		lst = lst->next;
		token = lst->content;
	}
	if (token->type == PIPE)
		return (lst->next);
	return (aux);
}

int	check_redirect(t_list *lst)
{
	t_list	*aux;
	t_token	*token;
	int		i;

	i = 0;
	token = lst->content;
	aux = lst;
	while (aux)
	{
		if (!aux->next)
			break ;
		if (token->type == 3 || token->type == 4)
			i++;
		if (token->type == 1 && !is_type(lst, PIPE))
			i++;
		if (token->type == PIPE)
			break ;
		aux = aux->next;
		token = aux->content;
	}
	if (i > 0)
		return (1);
	return (0);
}

static void	open_fds(t_list *lst, int count)
{
	int		fd;
	t_token	*token;
	int		i;

	i = 0;
	while (i <= count)
	{
		token = lst->content;
		if (token->type == 3)
		{
			fd = open(token->string, O_WRONLY | O_CREAT | O_APPEND, 0666);
			close(fd);
		}
		else if (token->type == 4)
		{
			fd = open(token->string, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			close(fd);
		}
		else if (token->type == PIPE)
			break ;
		lst = lst->next;
		i++;
	}
}

int	exec_redirect(t_list *lst, int flag)
{
	char	*output;
	char	*input;
	int		fd;
	int		flags;
	int		redirect;

	redirect = count_types(lst, 3);
	redirect += count_types(lst, 4);
	flags = 0;
	if (is_type(lst, 1))
	{
		input = find_input(lst);
		if (access(input, F_OK) == 0)
		{
			fd = open(input, O_RDONLY, 0666);
			if (dup2(fd, STDIN_FILENO) == -1)
				return (1);
			close(fd);
		}
		else
			return (0);	// Error: no such file or directory
	}
	if (redirect > 1)
		open_fds(lst, redirect);
	if (is_type(lst, 3) || is_type(lst, 4))
	{
		output = find_output(lst, flag);
		if (is_type(lst, 3) == 1)
			flags = O_CREAT | O_APPEND | O_WRONLY;
		else if (is_type(lst, 4) == 1)
			flags = O_CREAT | O_TRUNC | O_WRONLY;
		fd = open(output, flags, 0666);
		if (fd < 0)
			return (1);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (1); // Error: dup2
		close(fd);
	}
	return (0);
}
