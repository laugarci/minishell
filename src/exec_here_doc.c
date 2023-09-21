/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:29:17 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/21 19:11:14 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "minishell_defs.h"
#include "libft_bonus.h"
#include "parser.h"
#include <readline/readline.h>
#include <readline/history.h>

#define	READ_END 0
#define WRITE_END 1

//falta solucionar que si hay una redireccion > se haga tambien

int	find_cat(t_list *aux)
{
	t_token	*token;
	int		i;
	t_list	*tmp;

	tmp = aux;
	token = tmp->content;
	i = 0;
	while (token->type != 2)
	{
		tmp = tmp->next;
		token = tmp->content;
		if (ft_strncmp(token->string, "cat\0", 4) == 0)
		{
			tmp = tmp->next;
			token = tmp->content;
			if (token->type == 2)
			{
				i = 1;
				break ;
			}
		}
	}
	return (i);
}

char	*find_del(t_list *lst, int count)
{
	char	*del;
	t_token	*token;
	int		total;

	token = lst->content;
	if (token->type != 2)
	{
		total = count_types(lst, 2) - (count) + 1;
		token = lst->content;
		if (token->type != 2)
		{
			while (token->type != 2)
			{
				lst = lst->next;
				token = lst->content;
				if (token->type == 2)
					total--;
			}
		}
		while (total > 0)
		{
			lst = lst->next;
			token = lst->content;
			if (token->type == 2)
				total--;
		}
	}
	else
	{
		if (count_types(lst, 2) != count)
		{
			lst = lst->next;
			token = lst->content;
		}
	}
	del = malloc(sizeof(char) * ft_strlen(token->string) + 1);
	if (!del)
		return (NULL);
	ft_strlcpy(del, token->string, ft_strlen(token->string) + 1);
	return (del);
}

void	here_doc_cmd(t_list *lst, char *text)
{
	t_token	*token;

	token = lst->content;
	if (ft_strncmp(token->string, "cat\0", 3) == 0)
	{
		if ((process_is_type(lst, 3) || process_is_type(lst, 4)))
			exec_redirect(lst, 0);
		write(1, text, ft_strlen(text));
	}
	if (!is_type(lst, PIPE))
		exit(1);
}

int		is_cat(t_list *lst)
{
	t_list *aux;
	t_token	*token;

	aux = lst;
	token = aux->content;
	if (ft_strncmp(token->string, "cat\0", 4) == 0)
			return (1);
	return (0);
}

int	count_hd(t_list	*lst)
{
	int	c;
	t_list	*tmp;
	t_token	*aux;

	tmp = lst;
	c = 0;
	while(tmp->next)
	{
		aux = tmp->content;
		if (aux->type == 2)
			c++;
		tmp = tmp->next;
	}
	return(c);
}

int	here_doc(t_list *lst, char **env)
{
	char	*del;
	char	*input;
	char	*text;
	int		count;
	t_list	*aux;

	aux = lst;
	count = count_hd(aux);
	while (count > 0)
	{
		text = NULL;
		del = find_del(aux, count);
		if (!process_is_type(aux, 2))
			while (!process_is_type(aux, 2))
				aux = aux->next;
		while(42)
		{
			input = readline("> ");
			if (ft_strncmp(input, del, ft_strlen(del) + 1) == 0)
				break ;
			text = ft_strjoin(text, input);
			text = ft_strjoin(text, "\n");
		}
//		if (is_cat(aux))
//		{
//			if (process_is_type(aux, TRUNC) || process_is_type(aux, APPEND))
//				here_doc_cmd(aux, text);
//			else
//			{
//				if (count == 1)
//					write(1, text, ft_strlen(text));
//			}
//		}
	//	else if ((process_is_type(aux, 3) || process_is_type(aux, 4)))
	//	{
	//		if (check_redirect(aux))
	//			exec_redirect(lst, 1);
	//		if (process_is_type(aux, -1)  && !is_cat(aux))
	//			exec_commands(aux, env);
	//	}
		if (is_type(lst, PIPE))
				aux = move_to_pipe(aux);
		count--;
	}
	return (0);
	env = NULL;
}
