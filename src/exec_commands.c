/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:00:39 by laugarci          #+#    #+#             */
/*   Updated: 2023/08/16 14:45:35 by laugarci         ###   ########.fr       */
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

	i = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
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
				return (1); // Error "No such file or directory"
		}
		else
			return (1); // Error "Permission denied"
	}
	else
		return (1); // Error no such file or directory
	return (0);
}

int	cmp_commands(t_list *lst, char **env)
{
	t_token	*token;
	int		num_pipes;
	int		num_args;

	token = lst->content;
	if (ft_strncmp(token->string, "cd ", 3) == 0
		|| ft_strncmp(token->string, "cd\0", 3) == 0)
		exec_cd(lst);
	else if (is_type(lst, 0) == 1 || is_type(lst, 3) || is_type(lst, 4))
	{
		num_pipes = count_chars(lst);
		exec_pipes(lst, env, num_pipes);
	}
	else if (is_type(lst, 3) == 1 || is_type(lst, 4) == 1)
	{
		num_args = count_args(lst);
		//exec_redirect(lst, num_args,  env);
	}
	else
		exec_commands(lst, env);
	return (0);
	free_double((void **)env);
	env = NULL;
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
		printf("zsh: command not found %s\n", token->string);
	return (0);
}

int	exec_commands(t_list *lst, char **env)
{
	t_token	*token;
	t_list	*tmp;
	pid_t	pid;
	int		i;
	char	**args;
	int		status;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	token = lst->content;
	pid = fork();
	if (pid == 0)
	{
		if (i == 2)
		{
			args = (char **)malloc(sizeof(char *) * 2);
			if (!args)
				return (1);
			args[0] = get_path(token->string, env);
			args[1] = NULL;
			if ((execve(args[0], args, env)) == -1)
				printf("zsh: command not found: %s\n", token->string);
		}
		else
			exec_commands_wf(lst, env, (i - 1));
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
	return (0);
}
