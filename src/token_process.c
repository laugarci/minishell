/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:34:52 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/19 19:29:26 by ffornes-         ###   ########.fr       */
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

static int	exp_token_util(char *string, t_token **tkn, t_list **lst)
{
	t_list	*aux;
	t_token	*token;

	aux = *lst;
	token = *tkn;
	if (!ft_strchr(string, ' ') || token->quotes > 0)
	{
		token->string = string;
		aux->content = token;
		return (1);
	}
	return (0);
}

static t_list	*exp_token(t_list *lst, t_token *tkn, char **envp)
{
	t_list	*new_list;
	t_list	*aux;
	char	*string;

	string = expand_evals(tkn->string, envp);
	if (!string)
		return (NULL);
	if (exp_token_util(string, &tkn, &lst))
		return (lst);
	new_list = save_tokens(string);
	if (!new_list)
		return (NULL);
	free(lst->content);
	free(string);
	lst->content = new_list->content;
	aux = new_list;
	new_list = new_list->next;
	free(aux);
	aux = lst->next;
	lst->next = new_list;
	while (new_list->next)
		new_list = new_list->next;
	new_list->content = aux->content;
	new_list->next = aux->next;
	return (lst);
}

static int	process_tokens_util(t_list **token_list)
{
	if (join_subtoken(token_list))
		return (12);
	clean_redirects(token_list);
	remove_duplicates(token_list);
	return (0);
}

int	process_tokens(t_list **token_list, char *envp[])
{
	t_list	*tmp_lst;
	t_token	*aux;

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
			tmp_lst = exp_token(tmp_lst, aux, envp);
			if (!tmp_lst)
				return (print_and_return(12));
		}
		tmp_lst = tmp_lst->next;
		aux = tmp_lst->content;
	}
	if (process_tokens_util(token_list))
		return (print_and_return(12));
	return (0);
}
