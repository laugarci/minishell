/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:29:17 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/22 17:30:58 by laugarci         ###   ########.fr       */
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

static char	*find_delimiter(t_list *lst, int id)
{
	t_token	*token;
	int		i;

	i = 0;
	while (lst && i < id)
	{
		token = lst->content;
		if (token->type == HERE_DOC)
			i++;
		lst = lst->next;
	}
	return (token->string);
}

char	*input_heredoc(char *del)
{
	char	*aux;
	char	*input;
	char	*text;

	while (42)
	{
		input = readline("> ");
		if (ft_strncmp(input, del, ft_strlen(del) + 1) == 0)
			break ;
		text = ft_strjoin(text, input);
		if (!text)
			break ;
		free(input);
		aux = text;
		text = ft_strjoin(text, "\n");
		free(aux);
		if (!text)
			return (NULL);
	}
	free(input);
	return (text);
}

int	*here_doc(t_list *lst, int id)
{
	char	*del;
	char	*text;
	int		fds[2];
	int		*out;

	del = find_delimiter(lst, id);
	text = input_heredoc(del);
	pipe(fds);
	out = malloc(sizeof(int));
	if (!out)
		return (NULL);
	*out = fds[0];
	write(fds[1], text, ft_strlen(text));
//	free(text);
	return (out);
}
