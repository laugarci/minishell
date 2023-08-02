/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:33:06 by ffornes-          #+#    #+#             */
/*   Updated: 2023/08/02 14:37:10 by ffornes-         ###   ########.fr       */
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
