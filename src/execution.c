/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:29:58 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/24 13:13:12 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "minishell_defs.h"
#include "parser.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static int	dup_hdoc(t_list *lst, t_exec_fds *exec_fds)
{
	t_token	*token;
	int		count;

	count = 0;
	while (lst)
	{
		token = lst->content;
		if (!token->string)
			break ;
		if (token->type == PIPE)
			break ;
		else if (token->type == HERE_DOC)
			count++;
		lst = lst->next;
	}
	count += exec_fds->hd_count - 1;
	if (dup2(exec_fds->hdoc_fds[count], STDIN_FILENO) == -1)
		return (1);
	return (0);
}

static int	dup_read(t_list *lst, t_exec_fds *exec_fds)
{
	int		fd;
	char	*input;

	input = NULL;
	fd = 0;
	if (count_types(lst, INFILE) || is_type(lst, HERE_DOC))
	{
		if (find_input(lst, &input, INFILE, HERE_DOC))
			return (126);
	}
	else
		return (0);
	if (input && process_is_type(lst, INFILE))
	{
		fd = open(input, O_RDONLY, 0666);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (1);
		close(fd);
	}
	else
		return (dup_hdoc(lst, exec_fds));
	return (0);
}

static int	dup_write(t_list *lst)
{
	int		fd;
	char	*output;

	output = NULL;
	fd = 0;
	if (count_types(lst, TRUNC) || is_type(lst, APPEND))
		find_input(lst, &output, TRUNC, APPEND);
	else
		return (0);
	if (output)
	{
		if (count_types(lst, APPEND) > 1 || count_types(lst, TRUNC) > 1)
			create_files(lst);
		if (is_type(lst, APPEND) == 1)
			fd = open(output, O_CREAT | O_APPEND | O_WRONLY, 0666);
		else if (is_type(lst, TRUNC) == 1)
			fd = open(output, O_CREAT | O_TRUNC | O_WRONLY, 0666);
		if (fd < 0)
			return (1);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (1); // Error: dup2
		close(fd);
	}
	return (0);
}

static int check_builtins(t_list *lst, t_list **env_lst, char **env)
{
	t_token *token;
	int		err;

	err = 0;
	token = lst->content;
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

static int	execution_utils(t_list *lst, t_list **env_lst, t_exec_fds *exec_fds, char **env)
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
		err = dup_read(lst, exec_fds);
		if (err)
			exit(err); // Must print error message before 
		else if (exec_fds->read_pipe_fds[0] >= 0)
		{
			if (!count_types(lst, INFILE) && !count_types(lst, HERE_DOC))
				if (dup2(exec_fds->read_pipe_fds[0], STDIN_FILENO) < 0)
					return(1);
			close(exec_fds->read_pipe_fds[0]);
		}
		if (dup_write(lst))
			exit(1);
		else if (is_type(lst, PIPE) && check_redirect(lst, TRUNC, APPEND) == 0)
		{
     		if (dup2(exec_fds->write_pipe_fds[1], STDOUT_FILENO) < 0)
				return (1);
			close(exec_fds->write_pipe_fds[1]);
		}
		token = lst->content;
		exit_check(lst);
		check_builtins(lst, env_lst, env);
		exit(err);
	}
	return (err);
}

int	execution(t_list *lst, t_list **env_lst, t_exec_fds *exec_fds, char **env)
{
	int	err;

	exit_check(lst);
	exec_fds->pipe_count = count_types(lst, PIPE) + 1;
	while (42)
	{
		if (is_type(lst, PIPE))
		{
			exec_fds->write_pipe_fds = malloc(sizeof(int) * 2);
			if (!exec_fds->write_pipe_fds)
				return (12); // Check clean exit
			pipe(exec_fds->write_pipe_fds);
			*exec_fds->next_read_fd = exec_fds->write_pipe_fds[0];
		}
		else
		{
			check_builtins(lst, env_lst, env);
			break ;
		}
		err = execution_utils(lst, env_lst, exec_fds, env);
		exec_fds->process_id++;
		exec_fds->hd_count += process_is_type(lst, HERE_DOC);
		lst = move_to_pipe(lst);
		if (exec_fds->write_pipe_fds)
			close(exec_fds->write_pipe_fds[1]);
		if (*exec_fds->read_pipe_fds >= 0)
			close(*exec_fds->read_pipe_fds);
		if (*exec_fds->next_read_fd >= 0)
		{
			*exec_fds->read_pipe_fds = *exec_fds->next_read_fd;
			*exec_fds->next_read_fd = -1;
		}
		else
			*exec_fds->read_pipe_fds = -1;

		exec_fds->pipe_count--;
		if (exec_fds->pipe_count == 0)
			break ;
	}
	// Aqui esperar todos los hijos XD! unfunnny business
	return (err);
}
