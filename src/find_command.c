/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 10:09:20 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/26 14:47:25 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"
#include "parser.h"
#include "libft_bonus.h"
#include <unistd.h>
#include <stdio.h>

char	*find_command(t_list *lst)
{
	size_t	total_length;
	t_token	*token;
	t_list	*current;
	int		i;
	char	*result;

	total_length = total_input_len(lst);
	result = malloc(sizeof(char) * (total_length + 1));
	if (!result)
		return (NULL);
	current = lst;
	i = 0;
	while (current->next)
	{
		token = current->content;
		if (token->type >= 0)
			break ;
		if (i > 0)
			result[i++] = ' ';
		ft_strlcpy(result + i, token->string, total_length);
		i += ft_strlen(token->string);
		current = current->next;
	}
	result[total_length] = '\0';
	return (result);
}

/*
static char	*allocate_output(t_token *token, )
{
		flag = 0;
		if (token->type == INFILE || token->type == TRUNC
			|| token->type == APPEND)
		{
			output = malloc(sizeof(char) * ft_strlen(token->string) + 1);
			if (!output)
				return (NULL);
			ft_strlcpy(output, token->string, ft_strlen(token->string) + 1);
			tmp = tmp->next;
			token = tmp->content;
			flag = 1;
			if (token->type != 3 && token->type != 4 && token->type != 1)
				break ;
		}
		if (flag == 0)
		{
			tmp = tmp->next;
			token = tmp->content;
		}
}
*/

char	*find_output(t_list *lst)
{
	t_list	*tmp;
	t_token	*token;
	char	*output;
	int		flag;

	tmp = lst;
	token = tmp->content;
	output = NULL;
	while (tmp)
	{
		flag = 0;
		if (token->type == INFILE || token->type == TRUNC
			|| token->type == APPEND)
		{
			output = malloc(sizeof(char) * ft_strlen(token->string) + 1);
			if (!output)
				return (NULL);
			ft_strlcpy(output, token->string, ft_strlen(token->string) + 1);
			tmp = tmp->next;
			token = tmp->content;
			flag = 1;
			if (token->type != 3 && token->type != 4 && token->type != 1)
				break ;
		}
		if (flag == 0)
		{
			tmp = tmp->next;
			token = tmp->content;
		}
	}
	return (output);
}

int	find_input(t_list *lst, char **dst, int type1, int type2)
{
	t_token	*token;

	token = lst->content;
	while (lst)
	{
		if (token->type == PIPE || !token->string)
			break ;
		if (token->type == type1 || token->type == type2)
		{
			*dst = token->string;
			if (token->type == INFILE)
			{
				if (access(*dst, F_OK))
					return (error_exec(token->string, \
							"No such file or directory\n", 1));
				else if (access(*dst, R_OK))
					return (error_exec(token->string, \
							"Permission denied\n", 1));
			}
		}
		lst = lst->next;
		token = lst->content;
	}
	return (0);
}
