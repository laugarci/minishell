/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:12:15 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/16 13:19:06 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include "libft_bonus.h"

#include <stdlib.h>
#include <stdio.h>

static t_list	*add_type(t_list *lst, int type1, int type2)
{
	t_token	*token;
	t_list	*new_list;
	t_list	*tmp;

	new_list = NULL;
	while (42)
	{
		token = lst->content;
		if (token->type == PIPE)
			break ;
		if (token->string && (token->type == type1 || token->type == type2))
		{
			tmp = ft_lstnew((void *)token);
			ft_lstadd_back(&new_list, ft_lstnew((void *)token));
		}
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (new_list);
}

static t_list	*organize_list_utils(t_list *new_list, t_list *aux, t_list *lst)
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
	return (new_list);
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
	aux = NULL;
	while (count--)
	{
		new_list = organize_list_utils(new_list, aux, lst);
		if (count)
		{
			token = new_token(ft_strdup("|"), PIPE, 0);
			ft_lstadd_back(&new_list, ft_lstnew((void *)token));
			lst = move_to_pipe(lst);
		}
		else
		{
			ft_lstadd_back(&new_list, ft_lstnew((void *)new_token(NULL, -1, -1)));
			return (new_list);
		}
	}
	return (lst);
}
