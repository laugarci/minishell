/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:29:17 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/22 12:15:54 by laugarci         ###   ########.fr       */
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

#define	READ_END 0
#define WRITE_END 1


char	*find_del(t_list *lst, int count)
{
	char	*del;
	t_token	*token;
	int		total;

	token = lst->content;
	if (token->type != 2)
	{
		total = count_types(lst, 2) - (count) + 1;
		token = lst->content;
		if (token->type != 2)
		{
			while (token->type != 2)
			{
				lst = lst->next;
				token = lst->content;
				if (token->type == 2)
					total--;
			}
		}
		while (total > 0)
		{
			lst = lst->next;
			token = lst->content;
			if (token->type == 2)
				total--;
		}
	}
	else
	{
		if (count_types(lst, 2) != count)
		{
			lst = lst->next;
			token = lst->content;
		}
	}
	del = malloc(sizeof(char) * ft_strlen(token->string) + 1);
	if (!del)
		return (NULL);
	ft_strlcpy(del, token->string, ft_strlen(token->string) + 1);
	return (del);
}

int		is_cat(t_list *lst)
{
	t_list *aux;
	t_token	*token;

	aux = lst;
	token = aux->content;
	if (ft_strncmp(token->string, "cat\0", 4) == 0)
			return (1);
	return (0);
}

int	count_hd(t_list	*lst)
{
	int	c;
	t_list	*tmp;
	t_token	*aux;

	tmp = lst;
	c = 0;
	while(tmp->next)
	{
		aux = tmp->content;
		if (aux->type == 2)
			c++;
		tmp = tmp->next;
	}
	return(c);
}

int	**pipe_hd(int num_hd)
{
	int	i;
	int	**fds;

	i = 0;
	fds = malloc(sizeof(int *) * num_hd);
	if (!fds)
		return (NULL);
	while (i < num_hd)
	{
		fds[i] = malloc(sizeof(int) * 2);
		if (!fds[i])
			return (NULL);
		pipe(fds[i]);
		i++;
	}
	return (fds);
}

int	*here_doc(t_list *lst)
{
	char	*del;
	char	*input;
	char	*text;
	int		count;
	int		**fds;

	count = count_hd(lst);
	fds = pipe_hd(count);
	text = NULL;
	while (count > 0)
	{
		del = find_del(lst, count);
		if (!process_is_type(lst, 2))
			while (!process_is_type(lst, 2))
				lst = lst->next;
		while(42)
		{
			input = readline("> ");
			if (ft_strncmp(input, del, ft_strlen(del) + 1) == 0)
				break ;
			text = ft_strjoin(text, input);
			text = ft_strjoin(text, "\n");
		}
		if (is_type(lst, PIPE))
			lst = move_to_pipe(lst);
		count--;
	}
	return (fds[0]);
}
