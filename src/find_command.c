/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 10:09:20 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/26 14:53:30 by laugarci         ###   ########.fr       */
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
	int		i;
	char	*result;

	total_length = total_input_len(lst);
	result = malloc(sizeof(char) * (total_length + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (lst->next)
	{
		token = lst->content;
		if (token->type >= 0)
			break ;
		if (i > 0)
			result[i++] = ' ';
		ft_strlcpy(result + i, token->string, total_length);
		i += ft_strlen(token->string);
		lst = lst->next;
	}
	result[total_length] = '\0';
	return (result);
}

t_list	*check_flag(t_list *lst, int flag)
{
	if (flag == 0)
		lst = lst->next;
	return (lst);
}

char	*find_output(t_list *lst)
{
	t_token	*token;
	char	*output;
	int		flag;

	output = NULL;
	while (lst)
	{
		token = lst->content;
		flag = 0;
		if (token->type == INFILE || token->type == TRUNC
			|| token->type == APPEND)
		{
			output = malloc(sizeof(char) * ft_strlen(token->string) + 1);
			if (!output)
				return (NULL);
			ft_strlcpy(output, token->string, ft_strlen(token->string) + 1);
			lst = lst->next;
			token = lst->content;
			flag = 1;
			if (token->type != 3 && token->type != 4 && token->type != 1)
				break ;
		}
		lst = check_flag(lst, flag);
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
