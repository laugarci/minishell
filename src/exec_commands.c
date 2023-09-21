/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:04:45 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/21 17:23:51 by laugarci         ###   ########.fr       */
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
#include "minishell_defs.h"
#include "libft_bonus.h"
#include "parser.h"

int	cmp_commands(t_list *lst, char **env)
{
	t_token	*token;
	int		num_pipes;
	int		err;

	token = lst->content;
	err = 0;
	exit_check(lst);
	if (ft_strncmp(token->string, "cd\0", 3) == 0)
		err = exec_cd(lst);
	else if (is_type(lst, 0) || is_type(lst, 3)
		|| is_type(lst, 4) || is_type(lst, 1) || is_type(lst, 2))
	{
		num_pipes = count_types(lst, PIPE);
		err = exec_pipes(env, num_pipes, lst);
	}
	else if (ft_strncmp(token->string, "echo\0", 5) == 0)
		err = exec_echo(lst);
	else if (ft_strncmp(token->string, "pwd\0", 4) == 0)
		err = exec_pwd();
	else if (ft_strncmp(token->string, "export\0", 7) == 0)
	{
		lst = lst->next;
		token = lst->content;
		builtin_export(token->string, env);
	}
	else if (ft_strncmp(token->string, "env\0", 4) == 0)
		err = exec_env(env);
	else if (ft_strncmp(token->string, "unset\0", 6) == 0)
		err = exec_unset(lst, env);
	else
		err = exec_commands(lst, env);
	return (check_error(err));
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
		return (-1);
	args[0] = get_path(ft_strtrim(token->string, " "), env);
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
		return (check_error(127));
//	free_double((void **)args);
	return (0);
}

int	exec_commands_nf(t_list *lst, char **env)
{
	char	**args;
	t_token	*token;

	token = lst->content;
	args = (char **)malloc(sizeof(char *) * 2);
	if (!args)
		return (-1);
	args[0] = get_path(ft_strtrim(token->string, " "), env);
	args[1] = NULL;
	if ((execve(args[0], args, env)) == -1)
		return (check_error(127));
	free_double((void **)args);
	return (0);
}

int	exec_commands(t_list *lst, char **env)
{
	pid_t	pid;
	int		i;
	int		status;
	char	*cmd;
	char	**split_cmd;

	cmd = find_command(lst);
	split_cmd = ft_split(cmd, '|');
	lst = save_tokens(split_cmd[0]);
	i = count_list(lst);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		set_or_return_state(MODE_SET, STATE_EXEC);
		signal_handler();
		ctrl_c(MODE_SET);
		if (i == 2)
			exec_commands_nf(lst, env);
		else
			exec_commands_wf(lst, env, (i - 1));
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
	if (WTERMSIG(status) == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		set_or_return_exit_status(MODE_SET, 130);
	}
	else if (WTERMSIG(status) == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 0);
		set_or_return_exit_status(MODE_SET, 131);
	}
	free(cmd);
	free_double((void **)split_cmd);
	ft_lstclear(&lst, (void *)free_token);
	return (0);
}
