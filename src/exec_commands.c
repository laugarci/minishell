/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:04:45 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/26 14:50:14 by laugarci         ###   ########.fr       */
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

static int	free_double_and_return(void **var, int value)
{
	free_double(var);
	return (value);
}

static t_list	*token_setup(t_list *lst)
{
	char	*cmd;

	cmd = find_command(lst);
	if (!cmd)
		return (NULL);
	lst = save_tokens(cmd);
	free(cmd);
	if (!lst)
		return (NULL);
	return (lst);
}

static int	setup_cmd(t_list *lst, char **cmd, int size, char **env)
{
	t_token	*token;
	int		i;
	int		err;

	i = 0;
	token = lst->content;
	err = get_path(token->string, env, &(cmd[i]));
	if (err)
		return (err);
	if (!cmd[i++])
		free_double_and_return((void **)cmd, 12);
	while (i < size - 1)
	{
		lst = lst->next;
		token = lst->content;
		cmd[i] = ft_strdup(token->string);
		if (!cmd[i++])
			free_double_and_return((void **)cmd, 12);
	}
	cmd[i] = NULL;
	return (0);
}

int	exec_commands(t_list *lst, char **env)
{
	int		i;
	char	**cmd;
	int		err;

	err = 0;
	lst = token_setup(lst);
	if (!lst)
		exit(print_error_and_return("Cannot allocate memory\n", 12));
	i = count_list(lst);
	cmd = malloc(sizeof(char *) * i);
	if (!cmd)
		exit(print_error_and_return("Cannot allocate memory\n", 12));
	err = setup_cmd(lst, cmd, i, env);
	if (err)
		exit(err);
	ft_lstclear(&lst, (void *)free_token);
	if ((execve(cmd[0], cmd, env)) == -1)
		exit(print_error_and_return("Execve failed\n", 1));
	exit(err);
}
