/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:29:42 by ffornes-          #+#    #+#             */
/*   Updated: 2023/08/10 13:33:31 by ffornes-         ###   ########.fr       */
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
	int		flag;

	if (is_empty(str))
		return (1);
	check_quote_state(str);
	flag = 0;
	if (ft_strchr(str, '|') || ft_strchr(str, '<') || ft_strchr(str, '>'))
	{
		str = clean_input(str);
		if (!str)
			return (-1);
		flag = 1;
	}
	lst = save_tokens(str);
	if (flag)
		free(str);
	if (!lst)
		return (1);
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
