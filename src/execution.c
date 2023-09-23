/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:29:58 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/23 13:31:56 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "minishell_defs.h"

int	execution(t_list *lst, t_list **env_lst, t_exec_fds *exec_fds, char **env)
{
	t_token	*token;
	int		pid;
	char	*input;
	char	*output;

	exit_check(lst);
	pid = fork();
	input = NULL;
	ouput = NULL;
	if (pid == 0)
	{
	// Mirar si tenim redireccions de lectura
	// Mirar si tenim redireccions descriptura
		if (count_types(lst, INFILE) || exec_fds->hd_count)
			if (find_input(lst, &input, INFILE, HERE_DOC))
				return (126);
		if (count_types(lst, TRUNC) || is_type(lst, APPEND))
			find_input(lst, &output, TRUNC, APPEND);
		if (input)
		{
			fd = open(input, O_RDONLY, 0666);
			if (dup2(fd, STDIN_FILENO) == -1)
				return (1);
			close(fd);
		}
		else // if (hay pipe)
		{
			// Dup2 & close exec_fds->pipe_fds[no se]
		}
		if (output)
		{
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
		else if (is_type(lst, PIPE))
		{

			// Acceder exec_fds->pipe_fds[el que toca]
			// Dup2 & closefd
		}

	}
	else
	{
		if (is_type(lst, PIPE))
		{
			//modificar esta funcion
			close_pipes_parent(exec_fds)
		}
	}
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
	exec_fds->process_id++;
	lst = move_to_pipe(lst);
	return (err);
	(void)exec_fds;
}
