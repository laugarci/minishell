/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:29:42 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/26 15:38:31 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "parser.h"

int	check_quote_state(char *input)
{
	int	i;
	int	state;

	i = 0;
	state = 0;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			if (!state)
				state = 1;
			else if (state == 1)
				state = 0;
		}
		else if (input[i] == '\"')
		{
			if (!state)
				state = 2;
			else if (state == 2)
				state = 0;
		}
		i++;
	}
	return (state);
}

int	parse_input(char **str, char *envp[])
{
	int		error_id;
	char	*out;
	char	*tmp;

	out = *str;
	error_id = check_invalid_chars(out);
	if (error_id == 1)
		return (44);
	else if (error_id == 2)
		return (45);
	out = expand_evals(out, envp);
	tmp = remove_quotes(out);
	*str = tmp;
	return (0);
}
