/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:12:15 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/15 13:08:03 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"

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

t_list	*organize_list(t_list *lst)
{
	t_list	*new_list;
	//t_token	*token;
	int		count;

	count = count_processess(lst);
	printf("Found %d processess\n", count);
	while (count--)
	{
		
	}
	new_list = lst;
	return (new_list);
}
