/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:29:42 by ffornes-          #+#    #+#             */
/*   Updated: 2023/08/10 15:18:12 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "libft_bonus.h"
#include "minishell.h"
#include "parser.h"

static int	is_empty(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

// IN CASE OF ERROR SET PERROR HERE AND CALL ERROR MESSAGE FROM THIS FUNCTION
int	parse_input(char *str, char *envp[], t_list **token_list)
{
	char	*input;
	t_list	*lst;

	if (is_empty(str))
		return (1);
	check_quote_state(str);
	if (ft_strchr(str, '|') || ft_strchr(str, '<') || ft_strchr(str, '>'))
		str = clean_input(str);
	lst = save_tokens(str);
//	free(str);
	if (!lst)
		return (1);
	// Must handle redirections with it's file directly 
	// 		next to it without a space in between like:
	// >HOLA.txt <<KELOKE ...
	process_tokens(&lst);
	if (!lst->content)
		return (1);
	*token_list = lst;
	return (0); // TEMP
	input = expand_evals(input, envp);
//	tmp = remove_quotes(input);
//	*str = tmp;
	return (0);
}
