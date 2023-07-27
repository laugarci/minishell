/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:29:42 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/27 14:55:08 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "parser.h"

// Must split all input by spaces and save each char* into a token forming a t_list type
// 	in which we'll store all tokens with it's type, quote state... etc.

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
	if (error_id == 1)
		return (44);
	else if (error_id == 2)
		return (45);
	else if (error_id)
		return (error_id);

	token_list = save_tokens(out);
	process_tokens(&token_list);

	// TESTING
	t_token		*token;
	token = token_list->content;
	while (1)
	{
		printf("Token = [String: %s]\t", token->string);
		printf("[Type: ");
		if (token->type == INFILE)
			printf("INFILE]");
		else if (token->type == HERE_DOC)
			printf("HERE_DOC]");
		else if (token->type == PIPE)
			printf("PIPE]");
		else if (token->type == O_APPEND)
			printf("OUTFILE APPEND]");
		else if (token->type == O_TRUNC)
			printf("OUTFILE TRUNC]");
		else
			printf("-1]");
		printf("\t[Quotes: %d]\n", token->quotes);
		token_list = token_list->next;
		token = token_list->content;
		if (!token->string)
			break ;
	}
	return (0);
	// ENDTESTS

	if (!token_list->content)
		return (1);
	out = expand_evals(out, envp);
	tmp = remove_quotes(out);
	*str = tmp;
	return (0);
}
