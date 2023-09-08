/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:04:45 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/08 14:59:16 by laugarci         ###   ########.fr       */
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
	t_token	*token;
	t_list	*tmp;
	int		i;

	i = count_list(lst);
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
				return (1); // Error "No such file or directory"
		}
		else
			return (1); // Error: "Permission denied"
	}
	else
		return (1); // Error no such file or directory
	return (0);
}

int	cmp_commands(t_list *lst, char **env)
{
	t_token	*token;
	int		num_pipes;
	char	*command;

	token = lst->content;
	command = find_command(lst);
	if (ft_strncmp(token->string, "cd ", 3) == 0
		|| ft_strncmp(token->string, "cd\0", 3) == 0)
		exec_cd(lst);
	else if (is_type(lst, 0) || is_type(lst, 3) || is_type(lst, 4))
	{
		num_pipes = count_types(lst, PIPE);
		exec_pipes(env, num_pipes, command, lst);
	}
	else if (is_type(lst, 2) == 1)
			here_doc(lst, env);
	else if (ft_strncmp(token->string, "echo ", 5) == 0)
		exec_echo(lst);
	else if (ft_strncmp(token->string, "pwd ", 4) == 0)
		exec_pwd();
	else
		exec_commands(lst, env);
	return (0);
}

int	exec_commands_wf(t_list *lst, char **env, int flags)
{
	char	**args;
	t_token	*token;
	int		i;
	t_list	*tmp;

	tmp = lst->next;
	token = lst->content;
	args = (char **)malloc(sizeof(char *) * (flags + 2));
	if (!args)
		return (1);
	args[0] = get_path(token->string, env);
	i = 0;
	while (i < flags)
	{
		token = tmp->content;
		args[i + 1] = token->string;
		tmp = tmp->next;
		i++;
	}
	args[flags + 1] = NULL;
	token = lst->content;
	if ((execve(args[0], args, env)) == -1)
		return(-1); // Error: szh: command not found
	return (0);
}

int	exec_commands_nf(t_list *lst, char **env)
{
	char	**args;
	t_token	*token;

	token = lst->content;
	args = (char **)malloc(sizeof(char *) * 2);
	if (!args)
		return (1);
	args[0] = get_path(token->string, env);
	args[1] = NULL;
	if ((execve(args[0], args, env)) == -1)
		printf("zsh: command not found: %s\n", token->string);
	return (0);
}

int	exec_commands(t_list *lst, char **env)
{
	pid_t	pid;
	int		i;
	int		status;
	
	i = count_list(lst);
	pid = fork();
	if (pid == -1)
		return (-1); // Error: fail pid
	if (pid == 0)
	{
		if (i == 2)
			exec_commands_nf(lst, env);
		else
			exec_commands_wf(lst, env, (i - 1));
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
	return (0);
}
