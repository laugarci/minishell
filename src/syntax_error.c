/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:56:30 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/13 17:13:46 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>

static int	print_error(char *error_message)
{
	char	*base;

	base = "minishell: syntax error near unexpected token `";
	printf("%s%s\'\n", base, error_message);
	return (1);
}

static int	check_tokens(t_token *token, int type)
{
	if (!token->string || (type == 4 && !token->type))
	{
		if (type >= 0 && type < 5)
			return (print_error("newline"));
		else if (type == 0)
			return (print_error("|"));
	}
	else if (type > 0 && type < 5 && token->type >= 0 && token->type < 5)
		return (print_error(token->string));
	return (0);
}

static int	check_quotes(char *str)
{
	int	i;
	int	state;

	i = 0;
	state = 0;
	while (str[i])
		state = quote_state(state, str[i++]);
	if (state == 1)
		return (print_error("\'"));
	else if (state == 2)
		return (print_error("\""));
	return (0);
}

int	syntax_error_check(t_list *lst)
{
	t_token	*token;
	int		type;
	int		error;
	int		state;

	token = lst->content;
	if (token->type == PIPE)
		return (print_error(token->string));
	state = 0;
	while (42)
	{
		type = token->type;
		lst = lst->next;
		token = lst->content;
		error = check_tokens(token, type);
		if (!token->string)
			break ;
		if (!error && (ft_strchr(token->string, '\'')
				|| ft_strchr(token->string, '\"')))
			error = check_quotes(token->string);
		if (error)
			return (error);
	}
	return (0);
}
