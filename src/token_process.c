/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:34:52 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/15 10:25:08 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

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

static t_list	*expansion_token(t_list *list, t_token *token, char *envp[], int *exit_status)
{
	t_list	*new_list;
	t_list	*aux;
	char	*string;

	string = expand_evals(token->string, envp, exit_status);
	if (!string)
		return (NULL);
	if (!ft_strchr(string, ' ') || token->quotes > 0)
	{
		token->string = string;
		list->content = token;
		return (list);
	}
	new_list = save_tokens(string);
	if (!new_list)
		return (NULL);
	free(list->content);
	free(string);
	list->content = new_list->content;
	aux = new_list;
	new_list = new_list->next;
	free(aux);
	aux = list->next;
	list->next = new_list;
	while (new_list->next)
		new_list = new_list->next;
	new_list->content = aux->content;
	new_list->next = aux->next;
	return (list);
}

int	process_tokens(t_list **token_list, char *envp[], int *exit_status)
{
	t_list	*tmp_lst;
	t_token	*aux;

	print_tokens(*token_list);
	tmp_lst = set_type(token_list);
	if (syntax_error_check(tmp_lst))
		return (258);
	if (process_subtokens(&tmp_lst))
		return (print_and_return(12));
	aux = tmp_lst->content;
	while (aux->string)
	{
		if (remove_quotes(&aux))
			return (print_and_return(12));
		if (ft_strchr(aux->string, '$') && (aux->quotes == 2 || !aux->quotes))
		{
			tmp_lst = expansion_token(tmp_lst, aux, envp, exit_status);
			if (!tmp_lst)
				return (print_and_return(12));
		}
		tmp_lst = tmp_lst->next;
		aux = tmp_lst->content;
	}
	if (join_subtoken(token_list))
		return (print_and_return(12));
	clean_redirects(token_list);
	remove_duplicates(token_list);
	return (0);
}
