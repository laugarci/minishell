/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:04:45 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/24 16:44:09 by ffornes-         ###   ########.fr       */
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
