/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:15:53 by ffornes-          #+#    #+#             */
/*   Updated: 2023/08/30 12:40:33 by ffornes-         ###   ########.fr       */
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

// ToDo: Check if after taking the redirection chars the string is empty. If empty then:
// 		syntax error near unexpected token `newline'
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

	string = expand_evals(token->string, envp);
	if (!ft_strchr(string,  ' '))
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

void	process_tokens(t_list **token_list, char *envp[])
{
	t_list	*tmp_lst;
	t_token	*aux;

	tmp_lst = *token_list;
	aux = tmp_lst->content;
	while (42)
	{
		if (aux->type < 0)
			aux->type = get_token_type(aux->string);
		if (ft_strchr(aux->string, '\'') || ft_strchr(aux->string, '\"'))
			aux = remove_quotes(aux);
		if (ft_strchr(aux->string, '$'))
			tmp_lst = expansion_token(tmp_lst, aux, envp);
		tmp_lst = tmp_lst->next;
		aux = tmp_lst->content;
		if (!aux->string)
			break ;
	}
	clean_redirects(token_list);
	*token_list = remove_duplicates(*token_list);
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
