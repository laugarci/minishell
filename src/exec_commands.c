/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:00:39 by laugarci          #+#    #+#             */
/*   Updated: 2023/07/04 15:21:20 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "libft.h"
#include "minishell.h"

char *ft_strncpy(char *destination, const char *source, size_t num)
{
	char *dest;
	const char *src;

	dest = destination;
	src = source;
	while (num > 0 && *src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
		num--;
    }
	while (num > 0)
	{
		*dest = '\0';
		dest++;
		num--;
	}
	return (destination);
}

int	ft_exec_commands(char* input)
{
	char	*space_pos;
	char	*command;
	char	*flags;
	char	**args;
	int		status;
	pid_t	pid;
	
	pid = fork();
	if (pid == 0)
	{
		space_pos = ft_strchr(input, ' ');
		if (space_pos != NULL)
		{
			command = (char *)malloc(sizeof(char) * ((space_pos - input) + 1));
			flags = (char *)malloc(sizeof(char) * (ft_strlen(space_pos + 1) + 1));
			if (!command || !flags)
				return (1);
			ft_strncpy(command, input, (space_pos - input));
			ft_strncpy(flags, space_pos + 1, (ft_strlen(space_pos + 1)));
			command[space_pos - input] = '\0';
			flags[ft_strlen(space_pos + 1)] = '\0';
			args = (char**)malloc(3 * sizeof(char*));
			args[0] = command;
			args[1] = flags;
			args[2] = NULL;
			execvp(command, args);
			free(command);
			free(flags);
			free(args);
		}
		else
		{
			args = (char**)malloc(sizeof(char *) * 2);
			args[0] = input;
			args[1] = NULL;
			execvp(input, args);
			free(args);
		}
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	return (0);
}

