/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_join_subtoken.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:17:45 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/04 19:20:29 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static char	*join_input(t_list *lst)
{
	t_token	*token;
	char	*aux;
	char	*out;

	token = lst->content;
	out = ft_strdup("");
	if (!out)
		printf("LEL\n"); // Error: Not enough memory
	while (token->type > 4)
	{
		aux = out;
		out = ft_strjoin(out, token->string);
		if (!out)
			printf("LEL\n"); // Error: Not enough memory
		free(aux);
		if (token->type == TOKEND)
			return (out);
		lst = lst->next;
		token = lst->content;
	}
	return (out);
}

static t_token	*get_subtoken(t_list *token_list)
{
	t_token	*token;
	char	*aux;

	token = token_list->content;
	aux = token->string;
	token->string = join_input(token_list);
	free(aux);
	token->type = -1;
	token->quotes = 0;
	return (token);
}

static void	remove_append_util(t_list *pre, t_list *current, t_token *tkn)
{
	t_list	*tmp;

	while (tkn->type < 6)
	{
		free_token(tkn);
		tmp = current;
		current = current->next;
		pre->next = current;
		free(tmp);
		tkn = current->content;
	}
	if (tkn->type == 6)
	{
		pre->next = current->next;
		tmp = current;
		free_token(tkn);
		free(tmp);
	}
}

t_list	*remove_append(t_list *list)
{
	t_list	*previous;
	t_list	*current;
	t_token	*token;

	current = list;
	token = current->content;
	while (token->type < 5)
	{
		previous = current;
		current = current->next;
		token = current->content;
	}
	remove_append_util(previous, current, token);
	return (list);
}

t_list	*join_subtoken(t_list **token_list)
{
	t_list	*list;
	t_token	*token;

	list = *token_list;
	token = list->content;
	while (token->string)
	{
		if (token->type != TOKEN_APPEND)
			list = list->next;
		else
		{
			token = get_subtoken(list);
			list = remove_append(list);
		}
		token = list->content;
	}
	return (*token_list);
}
