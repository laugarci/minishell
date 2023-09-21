/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:29:17 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/21 20:39:14 by laugarci         ###   ########.fr       */
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

//falta solucionar que si hay una redireccion > se haga tambien

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

void	here_doc_cmd(t_list *lst, char *text)
{
	t_token	*token;

	token = lst->content;
	if (ft_strncmp(token->string, "cat\0", 3) == 0)
		write(1, text, ft_strlen(text));
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

char	*here_doc(t_list *lst)
{
	char	*del;
	char	*input;
	static char	*text;
	int		count;
	t_list	*aux;

	aux = lst;
	count = count_hd(aux);
	text = NULL;
	while (count > 0)
	{
		del = find_del(aux, count);
		if (!process_is_type(aux, 2))
			while (!process_is_type(aux, 2))
				aux = aux->next;
		while(42)
		{
			input = readline("> ");
			if (ft_strncmp(input, del, ft_strlen(del) + 1) == 0)
				break ;
			text = ft_strjoin(text, input);
			text = ft_strjoin(text, "\n");
		}
//		if (is_cat(aux))
//		{
//			write(1, text, ft_strlen(text));
//			if (!is_type(lst, PIPE))
//				exit(0);
//		}
		if (is_type(lst, PIPE))
				aux = move_to_pipe(aux);
		count--;
	}
	return (text);
}
