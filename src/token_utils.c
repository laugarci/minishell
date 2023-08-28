/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:33:06 by ffornes-          #+#    #+#             */
/*   Updated: 2023/08/28 14:56:30 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_bonus.h"
#include "parser.h"
#include <stdlib.h>

void	free_token(void *var)
{
	t_token	*token;

	token = (t_token *)var;
	if (token)
	{
		free(token->string);
		free(token);
	}
}

static t_list	*remove_first_token(t_list *token_list, int *deleted)
{
	t_list	*tmp;

	if (((t_token *)(token_list->content))->type > 0)
	{
		tmp = token_list;
		token_list = token_list->next;
		ft_lstdelone(tmp, (void *)free_token);
		*deleted = 1;
	}
	return (token_list);
}

static void	remove_duplicates_loop(t_list *aux, t_list *previous, int deleted)
{
	t_list	*tmp;

	while (aux->next)
	{
		tmp = aux;
		aux = aux->next;
		if (!deleted && ((t_token *)(tmp->content))->type > 0)
		{
			ft_lstdelone(tmp, (void *)free_token);
			previous->next = aux;
			deleted = 1;
		}
		else
		{
			deleted = 0;
			previous = tmp;
		}
	}
}

t_list	*remove_duplicates(t_list *token_list)
{
	t_list	*aux;
	t_list	*previous;
	int		deleted;

	deleted = 0;
	token_list = remove_first_token(token_list, &deleted);
	aux = token_list;
	previous = aux;
	remove_duplicates_loop(aux, previous, deleted);
	return (token_list);
}
