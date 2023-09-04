/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_save.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:15:53 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/04 11:40:50 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "libft_bonus.h"
#include <stdlib.h>

t_list	*save_tokens(char *input)
{
	char	**inputs;
	t_list	*token_list;
	t_list	*aux;
	int		i;

	i = 0;
	inputs = split_input(input);
	if (!inputs)
		return (NULL);
	token_list = ft_lstnew(new_token(inputs[i], -1, -1));
	if (!token_list)
		return (NULL);
	while (inputs[i++])
	{
		aux = ft_lstnew(new_token(inputs[i], -1, -1));
		if (!aux)
		{
			ft_lstclear(&token_list, (void *)free_token);
			free(inputs);
			return (NULL);
		}
		ft_lstadd_back(&token_list, aux);
	}
	free(inputs);
	return (token_list);
}
