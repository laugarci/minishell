/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:29:58 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/26 19:35:16 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "minishell_defs.h"
#include "parser.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static int	builtin_check(t_list *lst, t_list **env_lst, char **env)
{
	t_token	*token;
	int		err;

	err = -1;
	token = lst->content;
	exit_check(lst, &err);
	if (ft_strncmp(token->string, "cd\0", 3) == 0)
		err = builtin_cd(lst, env_lst);
	else if (ft_strncmp(token->string, "echo\0", 5) == 0)
		err = exec_echo(lst);
	else if (ft_strncmp(token->string, "pwd\0", 4) == 0)
		err = exec_pwd();
	else if (ft_strncmp(token->string, "env\0", 4) == 0)
		err = exec_env(env);
	else if (ft_strncmp(token->string, "unset\0", 6) == 0)
		err = builtin_unset(lst, env_lst);
	else if (ft_strncmp(token->string, "export\0", 7) == 0)
		err = builtin_export(lst, env_lst);
	if (err >= 0)
	{
		set_or_return_exit_status(MODE_SET, err);
		return (err);
	}
	return (err);
}

static int	parent_exec(t_list *lst, t_list **env_lst, char **env, t_data *data)
{
	t_token *token;
	int		err;
	int		stdio_fds[2];

	token = lst->content;
	stdio_fds[0] = dup(STDIN_FILENO);
	stdio_fds[1] = dup(STDOUT_FILENO);
	err = dup_read(lst, data);
	if (err)
		return (err);
	err = -1;
	if (dup_write(lst))
		return (1);
	err = builtin_check(lst, env_lst, env);
	dup2(stdio_fds[0], STDIN_FILENO);
	dup2(stdio_fds[1], STDOUT_FILENO);
	return (err);
}

static int child_exec(t_list *lst, t_list **env_lst, char **env)
{
	t_token	*token;
	char	*aux;
	int		err;

	token = lst->content;
	aux = token->string;
	free(aux);
	if (!token->string)
		return (12);
	err = builtin_check(lst, env_lst, env);
	if (err >= 0)
		return (err);
	return (exec_commands(lst, env));
}

static void	execution_utils(t_list *lst, t_list **env_lst, t_data *data, char **env)
{
	int err;
	t_token *token;

	token = lst->content;
	err = dup_read(lst, data);
	if (err)
		exit(err); 
	else if (data->read_pipe_fds >= 0)
	{
		if (!p_type_count(lst, INFILE) && !p_type_count(lst, HERE_DOC))
			if (dup2(data->read_pipe_fds, STDIN_FILENO) < 0)
				exit(1);
		close(data->read_pipe_fds);
	}
	if (dup_write(lst))
		exit(1);
	else if (type_count(lst, PIPE) && !check_redirect(lst, TRUNC, APPEND))
	{
   		if (dup2(data->write_pipe_fds[1], STDOUT_FILENO) < 0)
			exit(1);
		close(data->write_pipe_fds[0]);
		close(data->write_pipe_fds[1]);
	}
	token = lst->content;
	err = child_exec(lst, env_lst, env);
	exit(err);
}

int	execution(t_list *lst, t_list **env_lst, t_data *data, char **env)
{
	int	err;
	int	status;
	int	pid;

	err = 0;
	pid = 1;
	while (data->process_id <= data->pipe_count)
	{
		if (data->pipe_count)
		{
			pipe(data->write_pipe_fds);
			data->next_read_fd = data->write_pipe_fds[0];
		}
		else if (parent_exec(lst, env_lst, env, data) >= 0)
			break ;
		pid = fork();
		if (pid < 0)
			return (1);
		if (pid == 0)
			execution_utils(lst, env_lst, data, env);
		data->process_id++;
		data->hd_count += p_type_count(lst, HERE_DOC);
		lst = move_to_pipe(lst);
		if (data->write_pipe_fds[1] > -1)
			close(data->write_pipe_fds[1]);
		if (data->read_pipe_fds >= 0)
			close(data->read_pipe_fds);
		if (data->next_read_fd >= 0)
		{
			data->read_pipe_fds = data->next_read_fd;
			data->next_read_fd = -1;
		}
		else
			data->read_pipe_fds = -1;
	}
	if (pid != 1)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			set_or_return_exit_status(MODE_SET, WEXITSTATUS(status));
		else
			set_or_return_exit_status(MODE_SET, 0);
		if (WTERMSIG(status) == SIGINT)
			return (set_or_return_exit_status(MODE_SET, 130));
		else if (WTERMSIG(status) == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 0);
			return (set_or_return_exit_status(MODE_SET, 131));
		}
	}
	return (err);
}
