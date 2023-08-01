/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:33:06 by ffornes-          #+#    #+#             */
/*   Updated: 2023/08/01 16:14:45 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_bonus.h"
#include "parser.h"
#include <stdlib.h>

void	free_token_list(t_list *token_list)
{
	t_token	*token;
	t_list	*aux;

	aux = token_list;
	token = aux->content;
	while (token->string)
	{
		free(token->string);
		free(token);
		free(aux);
		aux = aux->next;
		token = aux->content;
	}
}
