/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:15:53 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/26 17:34:40 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include "libft_bonus.h"
#include <stdlib.h>

t_list	*save_tokens(char *input)
{
	char	**inputs;
	t_list	*token_list;
	int		i;

	i = 0;
	inputs = ft_split(input, ' ');
	if (!inputs)
		return (NULL);
	token_list = malloc(sizeof(t_list) * double_charp_size(inputs));
	if (!token_list)
		return (NULL);
	token_list = ft_lstnew(new_token(inputs[0], -1, -1));
	while (inputs[i++])
		ft_lstadd_back(&token_list, ft_lstnew(new_token(inputs[i], -1, -1)));
	free(inputs);
	return (token_list);
}
