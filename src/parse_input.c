/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:29:42 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/26 17:33:39 by ffornes-         ###   ########.fr       */
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
	if (error_id == 1)
		return (44);
	else if (error_id == 2)
		return (45);

	token_list = save_tokens(out);

	// TESTING
	t_token		*token;
	token = token_list->content;
	while (1)
	{
		printf("Content: %s\n", token->string);
		if (!token_list->next)
			break ;
		token_list = token_list->next;
		token = token_list->content;
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
