/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:29:17 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/23 12:14:24 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "minishell_defs.h"
#include "libft_bonus.h"
#include "parser.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>

static char	*find_delimiter(t_list *lst, int id)
{
	t_token	*token;
	int		i;

	i = 0;
	token = lst->content;
	while (lst && i < id)
	{
		if (!token || !token->string)
			return (NULL);
		if (token->type == HERE_DOC)
			i++;
		lst = lst->next;
		token = lst->content;
	}
	if (token->type != HERE_DOC)
	{
		lst = lst->next;
		token = lst->content;
	}
	return (token->string);
}

static void	close_fds(int *fds)
{
	close(fds[1]);
	close(fds[0]);
}

static int	input_heredoc(char *del, int *fds)
{
	char	*aux;
	char	*input;
	char	*text;

	text = NULL;
	while (42)
	{
		input = readline("> ");
		if (ft_strncmp(input, del, ft_strlen(del) + 1) == 0)
			break ;
		text = ft_strjoin(text, input);
		free(input);
		if (!text)
			return (12);
		aux = text;
		text = ft_strjoin(text, "\n");
		free(aux);
		if (!text)
			return (12);
	}
	write(fds[1], text, ft_strlen(text));
	free(input);
	close_fds(fds);
	return (0);
}

static void	check_signal(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	set_or_return_exit_status(MODE_SET, WEXITSTATUS(status));
}

int	*here_doc(t_list *lst, int id)
{
	char	*del;
	int		fds[2];
	int		*out;
	int		pid;

	del = find_delimiter(lst, id);
	pipe(fds);
	pid = fork();
	if (pid == 0)
	{
		set_or_return_state(MODE_SET, STATE_HDOC);
		signal_handler();
		if (input_heredoc(del, fds))
			exit(12);
		exit(0);
	}
	close(fds[1]);
	check_signal(pid);
	out = malloc(sizeof(int));
	if (!out)
		return (NULL);
	*out = fds[0];
	return (out);
}
