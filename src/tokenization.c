/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:15:53 by ffornes-          #+#    #+#             */
/*   Updated: 2023/08/09 14:49:18 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include "libft_bonus.h"
#include <stdlib.h>
#include <stdio.h>

static int	get_token_type(char	*str)
{
	if (ft_strchr(str, '|'))
		if (!ft_strncmp(str, "|\0", 2))
			return (PIPE);
	if (ft_strchr(str, '<'))
	{
		if ((!ft_strncmp(str, "<\0", 2)) 
			|| (str[0] == '<' && str[1] && str[1] != '<'))
			return (INFILE);
		else if (!ft_strncmp(str, "<<\0", 3)
			|| (str[0] == '<' && str[1] == '<' && str[2]))
			return (HERE_DOC);
	}
	else if (ft_strchr(str, '>'))
	{
		if (!ft_strncmp(str, ">\0", 2) 
			|| (str[0] == '>' && str[1] && str[1] != '>'))
			return (O_TRUNC);
		else if (!ft_strncmp(str, ">>\0", 3)
			|| (str[0] == '>' && str[1] == '>' && str[2]))
			return (O_APPEND);
	}
	return (-1);
}

static void	clean_redirects(t_list **lst)
{
	t_list	*tmp_lst;
	t_token	*token;
	char	*str;
	int		next;

	tmp_lst = *lst;
	token = tmp_lst->content;
	next = 0;
	while (token->string)
	{
		str = token->string;
		if (token->type > 0)
		{
			if (!ft_strncmp(str, "<\0", 2) || !ft_strncmp(str, "<<\0", 3) 
				|| !ft_strncmp(str, ">\0", 2) || !ft_strncmp(str, ">>\0", 3))
				next = token->type;
			else
				next = 0;
		}
		tmp_lst = tmp_lst->next;
		token = tmp_lst->content;
		if (next)
			token->type = next;
	}
}

/*
static void	remove_duplicates(t_list **token_list)
{

}
*/

void	process_tokens(t_list **token_list)
{
	t_list	*tmp_lst;
	t_token	*aux;

	tmp_lst = *token_list;
	aux = tmp_lst->content;
	while (1)
	{
		if (aux->type < 0)
			aux->type = get_token_type(aux->string);
		tmp_lst = tmp_lst->next;
		aux = tmp_lst->content;
		if (!aux->string)
			break ;
	}
	clean_redirects(token_list);
	//remove_duplicates(token_list);
}

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
