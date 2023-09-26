/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:04:45 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/26 12:20:17 by ffornes-         ###   ########.fr       */
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

static t_list	*token_setup(t_list *lst)
{
	char	*cmd;
	char	**split_cmd;

	cmd = find_command(lst);
	if (!cmd)
		return (NULL);
	split_cmd = ft_split(cmd, '|');
	if (!split_cmd)
	{
		free(cmd);
		return (NULL);
	}
	lst = save_tokens(split_cmd[0]);
	if (!lst)
	{
		free(cmd);
		free_double((void **)split_cmd);
		return (NULL);
	}
	free(split_cmd);
	return (lst);
}

static int	setup_cmd(t_list *lst, char **cmd, int size)
{
	t_token	*token;
	int		i;

	i = 0;
	token = lst->content;
	cmd[i] = get_path(token->string, env);
	if (!cmd[i++])
	{
		free_double((void **)cmd);
		return (12);
	}
	while (i < size - 1)
	{
		lst = lst->next;
		token = lst->content;
		cmd[i] = ft_strdup(token->string);
		if (!cmd[i++])
		{
			free_double((void **)cmd);
			return (12);
		}
	}
	cmd[i] = NULL;
	return (0);
}

int	exec_commands(t_list *lst, char **env)
{
	int		i;
	char	**cmd;

	lst = token_setup(lst);
	i = count_list(lst);
	cmd = malloc(sizeof(char *) * i);
	if (!cmd)
		exit(12);
	if (setup_cmd(lst, cmd, i))
		exit(12);
	if ((execve(cmd[0], cmd, env)) == -1)
		return (check_error(127));
	ft_lstclear(&lst, (void *)free_token);
	exit(0);
}
