/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:29:42 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/25 17:05:54 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "parser.h"

static int	check_invalid_chars(char *input)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			j++;
		else if (input[i] == '\"')
			k++;
		else if (input[i] == '\\')
			return (42);
		else if (input[i] == ';')
			return (43);
		else if (input[i] == '>' && input[i + 1] == '<')
			return (258);
		i++;
	}
	if (j % 2 != 0)		
		return (44);
	if (k % 2 != 0)
		return (45);
	return (0);
}

int	parse_input(char **str, char *envp[])
{
	int		error_id;
	char	*out;
	char	*tmp;

	out = *str;
	error_id = check_invalid_chars(out);
	if (error_id)
	{
		free(out);
		return (error_id);
	}
	out = expand_evals(out, envp);
	tmp = remove_quotes(out);
	*str = tmp;
	return (0);
}
