/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:04:45 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/24 15:21:52 by laugarci         ###   ########.fr       */
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

static int	count_hd(t_list	*lst)
{
	int		c;
	t_list	*tmp;
	t_token	*aux;

	tmp = lst;
	c = 0;
	while (tmp->next)
	{
		aux = tmp->content;
		if (aux->type == 2)
			c++;
		tmp = tmp->next;
	}
	return (c);
}

void	init_exec_fds(t_exec_fds *var)
{
	var->hdoc_fds = NULL;
	var->read_pipe_fds = malloc(sizeof(int));
	if (var->read_pipe_fds)
		*var->read_pipe_fds = -1;
	var->next_read_fd = malloc(sizeof(int));
	if (var->next_read_fd)
		*var->next_read_fd = -1;
	var->write_pipe_fds = NULL;
	var->hd_count = 0;
	var->hd_total = 0;
	var->process_id = 0;
	var->pipe_count = 0;
}

int	cmp_commands(t_list *lst, t_list **env_lst, char **env)
{
	int			process_count;
	int			i;
	t_exec_fds	exec_fds;

	init_exec_fds(&exec_fds);
	if (!exec_fds.read_pipe_fds || !exec_fds.next_read_fd)
		return (12);
	process_count = count_types(lst, PIPE);
	exec_fds.pipe_count = process_count;
	if (!process_count)
		process_count = 1;
	exec_fds.hd_total = count_hd(lst);
	i = 0;
	if (exec_fds.hd_total)
	{
		exec_fds.hdoc_fds = malloc(sizeof(int) * exec_fds.hd_total);
		if (!exec_fds.hdoc_fds)
			return (12);
		while (i < exec_fds.hd_total)
		{
			exec_fds.hdoc_fds[i] = here_doc(lst, i);
			if (exec_fds.hdoc_fds[i] < 0)
				printf("ERROR\n"); // Error
			i++;
		}
	}
	set_or_return_state(MODE_SET, STATE_EXEC);
	signal_handler();
	i = 0;
	execution(lst, env_lst, &exec_fds, env);
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
		signal_display(MODE_SET);
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
