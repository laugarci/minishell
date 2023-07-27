/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:15:53 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/27 17:26:42 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include "libft_bonus.h"
#include <stdlib.h>

static int	get_token_type(char	*str)
{
	if (!ft_strncmp(str, "|\0", 2))
		return (PIPE);
	else if (!ft_strncmp(str, "<\0", 2))
		return (INFILE);
	else if (!ft_strncmp(str, "<<\0", 3))
		return (HERE_DOC);
	else if (!ft_strncmp(str, ">\0", 2))
		return (O_TRUNC);
	else if (!ft_strncmp(str, ">>\0", 3))
		return (O_APPEND);
	return (-1);
}

void	process_tokens(t_list **token_list)
{
	t_list	*tmp_lst;
	t_token	*aux;
	t_token	*tmp;

	tmp_lst = *token_list;
	aux = tmp_lst->content;
	while (1)
	{
		if (aux->type < 0)
		{
			aux->type = get_token_type(aux->string);
			if (aux->type > 0)
			{
				tmp_lst = tmp_lst->next;
				tmp = tmp_lst->content;
				tmp->type = aux->type;
			}
		}
		tmp_lst = tmp_lst->next;
		aux = tmp_lst->content;
		if (!aux->string)
			break ;
	}
}

t_list	*save_tokens(char *input)
{
	char	**inputs;
	t_list	*token_list;
	int		i;

	i = 0;
	// Must not split by spaces exactly. Must check first if commas are open, and if they're
	// then spaces don't count towards the split.
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
