/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:07:29 by laugarci          #+#    #+#             */
/*   Updated: 2023/08/15 18:18:18 by laugarci         ###   ########.fr       */
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
	char *output;
	int	fd;

	output = find_output(lst);
	fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
