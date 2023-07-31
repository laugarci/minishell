/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:29:42 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/31 19:06:02 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "libft_bonus.h"
#include "minishell.h"
#include "parser.h"

static int	check_error(int error_id)
{
	if (error_id == 1)
		return (44);
	else if (error_id == 2)
		return (45);
	return (error_id);
}

// IN CASE OF ERROR SET PERROR HERE AND CALL ERROR MESSAGE FROM THIS FUNCTION
int	parse_input(char *str, char *envp[], t_list **token_list)
{
	int		error_id;
	char	*out;
	t_list	*lst;

	out = str;
	error_id = check_quote_state(out);
	if (!error_id)
		error_id = clean_input(&out);
	if (error_id)
		return (check_error(error_id));
	lst = save_tokens(out);
	if (!lst)
		return (1); // Mem error
	// Must handle redirections with it's file directly next to it without a space in between like:
	// >HOLA.txt <<KELOKE ...
	process_tokens(&lst);
	if (!lst->content)
		return (1);
	*token_list = lst;

	return (0);

	out = expand_evals(out, envp);
//	tmp = remove_quotes(out);
//	*str = tmp;
	return (0);
}
