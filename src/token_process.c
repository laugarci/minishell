/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:34:52 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/08 19:54:19 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
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
			return (TRUNC);
		else if (!ft_strncmp(str, ">>\0", 3)
			|| (str[0] == '>' && str[1] == '>' && str[2]))
			return (APPEND);
	}
	return (-1);
}

// ToDo: Check if after taking the redirection chars the string is empty.
// 		If empty then: syntax error near unexpected token `newline'
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

static t_list	*expansion_token(t_list *list, t_token *token, char *envp[])
{
	t_list	*new_list;
	t_list	*aux;
	char	*string;

	string = expand_evals(token, token->string, envp);
	if (!ft_strchr(string, ' ') || token->quotes > 0)
	{
		token->string = string;
		list->content = token;
		return (list);
	}
	new_list = save_tokens(string);
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

static t_list	*set_type(t_list **token_list)
{
	t_list	*tmp_lst;
	t_token	*aux;

	tmp_lst = *token_list;
	aux = tmp_lst->content;
	while (aux->string)
	{
		if (aux->type < 0)
			aux->type = get_token_type(aux->string);
		tmp_lst = tmp_lst->next;
		aux = tmp_lst->content;
	}
	return (*token_list);
}

static int	syntax_error_check(t_list *lst)
{
	t_token *token;
	int		type;
	char	*error_message;

	token = lst->content;
	error_message = "minishell: syntax error near unexpected token `";
	if (token->type == PIPE)
	{
		printf("%s%s\'\n", error_message, token->string);
		return (1);
	}
	while (42)
	{
		type = token->type;
		lst = lst->next;
		token = lst->content;
		if (!token->string || (type == 4 && !token->type))
		{
			if (type >= 0 && type < 5)
				printf("%snewline\'\n", error_message);
			else if (type == 0)
				printf("%s|\'\n", error_message); 
			return (1);
		}
		else if (type > 0 && type < 5 && token->type >= 0 && token->type < 5)
		{
			printf("%s%s\'\n", error_message, token->string);
			return (1);
		}
	}
	return (0);
}

void	process_tokens(t_list **token_list, char *envp[])
{
	t_list	*tmp_lst;
	t_token	*aux;

	tmp_lst = set_type(token_list);
	if (syntax_error_check(tmp_lst))
		return ;
	tmp_lst = process_subtokens(&tmp_lst);
	aux = tmp_lst->content;
	while (aux->string)
	{
		if (ft_strchr(aux->string, '\'') || ft_strchr(aux->string, '\"'))
			aux = remove_quotes(aux);
		else
			aux->quotes = 0;
		if (ft_strchr(aux->string, '$') && (aux->quotes == 2 || !aux->quotes))
			tmp_lst = expansion_token(tmp_lst, aux, envp);
		tmp_lst = tmp_lst->next;
		aux = tmp_lst->content;
	}
	*token_list = join_subtoken(token_list);
	clean_redirects(token_list);
	*token_list = remove_duplicates(*token_list);
}
