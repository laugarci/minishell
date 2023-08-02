/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:29:42 by ffornes-          #+#    #+#             */
/*   Updated: 2023/08/02 19:28:21 by ffornes-         ###   ########.fr       */
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

static int	basic_input_checks(char **input)
{
	int		error;

	error = check_quote_state(*input);
	if (!error)
		if (ft_strchr(*input, '|') 
			|| ft_strchr(*input, '<') 
			|| ft_strchr(*input, '>'))
			error = clean_input(input);
	return (error);
}

// IN CASE OF ERROR SET PERROR HERE AND CALL ERROR MESSAGE FROM THIS FUNCTION
int	parse_input(char *str, char *envp[], t_list **token_list)
{
	int		error_id;
	char	*input;
	t_list	*lst;

	if (is_empty(str))
		return (1);
	error_id = basic_input_checks(&str);
	if (error_id)
		return (check_error(error_id));
	lst = save_tokens(str); // Leak here
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
