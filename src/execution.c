/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:29:58 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/24 17:37:05 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "minishell_defs.h"
#include "parser.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int	cmp_commands(t_list *lst, t_list **env_lst, char **env)
{
	int			process_count;
	int			i;
	t_data		data;

	init_data(&data);
	if (!data.read_pipe_fds || !data.next_read_fd)
		return (12);
	process_count = type_count(lst, PIPE);
	data.pipe_count = process_count;
	if (!process_count)
		process_count = 1;
	data.hd_total = type_count(lst, HERE_DOC);
	i = 0;
	if (data.hd_total)
	{
		data.hdoc_fds = malloc(sizeof(int) * data.hd_total);
		if (!data.hdoc_fds)
			return (12);
		while (i < data.hd_total)
		{
			data.hdoc_fds[i] = here_doc(lst, i);
			if (data.hdoc_fds[i] < 0)
				printf("ERROR\n"); // Error
			i++;
		}
	}
	set_or_return_state(MODE_SET, STATE_EXEC);
	signal_handler();
	execution(lst, env_lst, &data, env);
	return (0);
}

static int check_builtins(t_list *lst, t_list **env_lst, char **env)
{
	t_token *token;
	int		err;

	err = 0;
	token = lst->content;
	exit_check(lst);
	if (ft_strncmp(token->string, "cd\0", 3) == 0)
		err = exec_cd(lst);
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
	else
		err = exec_commands(lst, env);
	return (err);
}

static int	execution_utils(t_list *lst, t_list **env_lst, t_data *data, char **env)
{
	int	pid;
	int err;
	t_token *token;

	token = lst->content;
	err = 0;
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		err = dup_read(lst, data);
		if (err)
			exit(err); // Must print error message before 
		else if (data->read_pipe_fds[0] >= 0)
		{
			if (!p_type_count(lst, INFILE) && !p_type_count(lst, HERE_DOC))
				if (dup2(data->read_pipe_fds[0], STDIN_FILENO) < 0)
					return(1);
			close(data->read_pipe_fds[0]);
		}
		if (dup_write(lst))
			exit(1);
		else if (type_count(lst, PIPE) && !check_redirect(lst, TRUNC, APPEND))
		{
     		if (dup2(data->write_pipe_fds[1], STDOUT_FILENO) < 0)
				return (1);
			close(data->write_pipe_fds[0]);
			close(data->write_pipe_fds[1]);
		}
		token = lst->content;
		exit_check(lst);
		check_builtins(lst, env_lst, env);
		exit(err);
	}
	return (err);
}

static int	single_process_check(t_list *lst, t_list **env_lst)
{
	t_token	*token;

	exit_check(lst);
	token = lst->content;
	if (!ft_strncmp(token->string, "cd\0", 3))
		return (exec_cd(lst));
	else if (ft_strncmp(token->string, "export\0", 7) == 0)
		return (builtin_export(lst, env_lst));
	return (-1);
}

int	execution(t_list *lst, t_list **env_lst, t_data *data, char **env)
{
	int	err;

	exit_check(lst);
	while (data->process_id <= data->pipe_count)
	{
		if (data->pipe_count)
		{
			data->write_pipe_fds = malloc(sizeof(int) * 2);
			if (!data->write_pipe_fds)
				return (12); // Check clean exit
			pipe(data->write_pipe_fds);
			*data->next_read_fd = data->write_pipe_fds[0];
		}
		else if (single_process_check(lst, env_lst) >= 0)
			break ;
		err = execution_utils(lst, env_lst, data, env);
		data->process_id++;
		data->hd_count += p_type_count(lst, HERE_DOC);
		lst = move_to_pipe(lst);
		if (data->write_pipe_fds)
			close(data->write_pipe_fds[1]);
		if (*data->read_pipe_fds >= 0)
			close(*data->read_pipe_fds);
		if (*data->next_read_fd >= 0)
		{
			*data->read_pipe_fds = *data->next_read_fd;
			*data->next_read_fd = -1;
		}
		else
			*data->read_pipe_fds = -1;
	}
	while (data->process_id--)
		wait(NULL);
	return (err);
}
