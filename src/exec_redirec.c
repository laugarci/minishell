/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:07:29 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/13 18:37:35 by laugarci         ###   ########.fr       */
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
static void	open_fds(t_list *lst, int count)
{
	int	fd;
	t_token *token;
	int	i;

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

int	count_args(t_list *lst)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	exec_redirect(t_list *lst)
{
	char	*output;
	int		fd;
	int		flags;
	int		redirect;

	redirect = count_types(lst, 3);
	redirect += count_types(lst, 4);
	output = find_output(lst);
	if (redirect > 1)
		open_fds(lst, redirect);
	flags = O_WRONLY | O_CREAT;
	if (is_type(lst, 3) == 1)
		flags = flags | O_APPEND;
	else if (is_type(lst, 4) == 1)
		flags = flags | O_TRUNC;
	fd = open(output, flags, 0666);
	if (fd < 0)
		return (1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (1);
	close(fd);
	return (0);
}
