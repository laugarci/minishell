/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_organize_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 13:10:29 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/16 13:12:28 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include "libft_bonus.h"
#include <stdlib.h>
#include <stdio.h>

int	count_processess(t_list *lst)
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

void	join_lists(t_list **dst, t_list *src)
{
	t_token	*token;
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
