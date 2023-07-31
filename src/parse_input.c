/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:29:42 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/31 18:42:35 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "parser.h"

// DEBUGGING
static void	print_tokens(t_list *lst)
{
	t_token		*token;

	token = lst->content;
	while (1)
	{
		printf("Token = [String: %s]\t", token->string);
		printf("[Type: ");
		if (token->type == INFILE)
			printf("INFILE]");
		else if (token->type == HERE_DOC)
			printf("H_DOC]");
		else if (token->type == PIPE)
			printf("PIPE]");
		else if (token->type == O_APPEND)
			printf("O_APPEND]");
		else if (token->type == O_TRUNC)
			printf("O_TRUNC]");
		else
			printf("-1]");
		printf("\t[Quotes: %d]\n", token->quotes);
		lst = lst->next;
		token = lst->content;
		if (!token->string)
			break ;
	}
}

static int	check_error(int error_id)
{
	if (error_id == 1)
		return (44);
	else if (error_id == 2)
		return (45);
	return (error_id);
}

int	parse_input(char **str, char *envp[])
{
	int		error_id;
	char	*out;
	char	*tmp;
	t_list	*token_list;

	out = *str;
	error_id = check_quote_state(out);
	if (!error_id)
		error_id = clean_input(&out);
	if (error_id)
		return (check_error(error_id));
	token_list = save_tokens(out);
	if (!token_list)
		return (1); // Mem error
	// Must handle redirections with it's file directly next to it without a space in between like:
	// >HOLA.txt <<KELOKE ...
	process_tokens(&token_list);
	if (!token_list->content)
		return (1);
	print_tokens(token_list); // DEBUGGING
	out = expand_evals(out, envp);
	tmp = remove_quotes(out);
	*str = tmp;
	return (0);
}
