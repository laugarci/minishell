/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:12:15 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/15 19:49:36 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include "libft_bonus.h"

#include <stdlib.h>
#include <stdio.h>

// TYPES:
// 		1	INFILE
// 		2	HERE_DOC
// 		3	APPEND
// 		4	TRUNC
//
// ORDER:
// 		COMMAND		INFILE / H_DOC / ARG		OUTFILE / PIPE

static int	count_processess(t_list *lst)
{
	t_token	*token;
	int		i;

	i = 1;
	while (42)
	{
		token = lst->content;
		if (token->type == PIPE)
			i++;
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (i);
}

static t_list	*add_type(t_list *lst, int type1, int type2)
{
	t_token	*token;
	t_list	*new_list;

	new_list = NULL;
	while (42)
	{
		token = lst->content;
		if (token->type == PIPE)
			break ;
		if (token->string && (token->type == type1 || token->type == type2))
			ft_lstadd_back(&new_list, ft_lstnew((void *)token));
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (new_list);
}

static void	join_lists(t_list **dst, t_list *src)
{
	t_token *token;
	t_list	*aux;
	t_list	*previous;

	aux = *dst;
	token = aux->content;
	while (42)
	{
		previous = aux;
		if (!aux->next)
			break ;
		aux = aux->next;
		token = aux->content;
	}
	previous->next = src;
}

t_list	*organize_list(t_list *lst)
{
	t_list	*new_list;
	t_list	*aux;
	int		count;
	t_token	*token;

	count = count_processess(lst);
	if (!count)
		return (lst);
	new_list = NULL;
	while (count--)
	{
		if (new_list)
		{
			aux = add_type(lst, -1, -1);
			join_lists(&new_list, aux);
		}
		else
			new_list = add_type(lst, -1, -1);
		aux = add_type(lst, INFILE, HERE_DOC);
		if (aux)	
			join_lists(&new_list, aux);
		aux = add_type(lst, APPEND, TRUNC);
		if (aux)	
			join_lists(&new_list, aux);
		if (count)
		{
			token = new_token(ft_strdup("|"), PIPE, 0);
			ft_lstadd_back(&new_list, ft_lstnew((void *)token));
			lst = move_to_pipe(lst);
		}
		else
			return (new_list);
	}
	printf("HERE\n");
	return (lst);
}
