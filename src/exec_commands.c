/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:00:39 by laugarci          #+#    #+#             */
/*   Updated: 2023/08/04 11:02:04 by laugarci         ###   ########.fr       */
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
#include "libft_bonus.h"
#include "parser.h"

int	exec_cd(t_list *lst)
{
	t_token *token;
	t_list	*tmp;
	int		i = 0;

	tmp = lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	tmp = lst->next;
	token = tmp->content;
	if (i == 2)
	{
		if (chdir(getenv("HOME")) == 1)
			return (1);
	}
	else if (access((token->string), F_OK) != -1)
	{
		if (access((token->string), R_OK) != -1)
		{
			if (chdir(token->string) == -1)
			{
				printf("minishell: cd: %s", token->string);
				printf(": No such file or directory\n");
				return (1);
			}
		}
		else
		{
			printf("minishell: cd: %s: Permission denied\n", token->string);
			return(1);
		}
	}
	else
	{
		printf("minishell: cd: %s\n: No such file or directory\n", token->string);
		return (1);
	}
	return (0);
}

int	cmp_commands(t_list *lst, char **env)
{
	t_token *token;

	token = lst->content;
	env = NULL;
	if (ft_strncmp(token->string, "cd ", 3) == 0 || ft_strncmp(token->string, "cd\0", 3) == 0)
		exec_cd(lst);
/*	char	**commands;
	int		num_pipes;

	commands = ft_split(input, ' ');
	else if (is_pipe(input) == 1)
	{
		num_pipes = count_chars(input, '|');
		exec_pipes(input, env, num_pipes);
	}
	else
		exec_commands(input, env);
	free_double((void **)commands);
	*/
	return (0);
}

int	exec_commands_wf(char *space_pos, char *input, char **env, char **split_com)
{
	int		i;
	char	**flags;
	char	**args;
	int		count_flags;

	count_flags = count_chars(input, '-');
	flags = ft_split(space_pos, ' ');
	args = (char **)malloc(sizeof(char *) * (count_flags + 3));
	if (!args)
		return (1);
	args[0] = get_path(split_com, env);
	i = 0;
	while (i <= count_flags)
	{
		args[i + 1] = flags[i];
		i++;
	}
	if (count_flags == 0)
		args[2] = NULL;
	else
		args[count_flags + 1] = NULL;
	if ((execve(args[0], args, env)) == -1)
		printf("zsh: command not found: %s\n", input); //hay que quitar las flags
	free_double((void **)flags);
	free_double((void **)args);
	return (0);
}

int	exec_commands(char *input, char **env)
{
	char	*space_pos;
	char	**args;
	int		status;
	char	**split_command;
	pid_t	pid;

	input = ft_strtrim(input, " ");
	split_command = ft_split(input, ' ');
	pid = fork();
	if (pid == 0)
	{
		space_pos = ft_strchr(input, ' ');
		if (space_pos != NULL)
			exec_commands_wf(space_pos, input, env, split_command);
		else
		{
			args = (char **)malloc(sizeof(char *) * 2);
			if (!args)
				return (1);
			args[0] = get_path(split_command, env);
			args[1] = NULL;
			if ((execve(args[0], args, env)) == -1)
				printf("zsh: command not found: %s\n", input);
			free_double((void **)args);
		}
		free_double((void **)split_command);
		free_double((void **)split_command);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
	return (0);
}
