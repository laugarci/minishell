/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:01:38 by laugarci          #+#    #+#             */
/*   Updated: 2023/06/30 15:15:25 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include "libft.h"
#include "minishell.h"

void	exec_command(char *command, char *flags[])
{
	pid_t pid;

	pid = fork();
	execvp(command, flags);
}

void	ft_exec_command(int ac, char **av)
{
	char *command;
	int i;
	char **flags

	i = 1;
	flags = malloc(sizeof(char *) * ac);
	command = malloc(sizeof(char) * ft_strlen(av[1]) + 1);
	if (!command || !flags)
		return ;
	command = av[1];
	while (i <= ac)
	{
		flags[i - 1] = argv[i]
			i++;
	}
	flags[i - 1] = NULL;
	exec_command(command, flags);
	free(flags);
	free(command);
}
