/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:48:00 by ffornes-          #+#    #+#             */
/*   Updated: 2023/08/10 13:23:16 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static int	check_character(char *str, int i)
{
	if (str[i] == '|')
	{
		if ((i > 0 && str[i - 1] == '|') || str[i + 1] == '|')
			return (-1);
		if (i > 0 && str[i - 1] != ' ')
			return (i);
		else if (str[i + 1] != ' ')
			return (i);
	}
	else if (str[i] == '<' || str[i] == '>')
	{
		if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
			return (-2);
		else if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
			return (-2);
		if (i > 0 && str[i] == '>' && str[i - 1] == '<')
			return (-2);
		if (i > 0 && str[i - 1] != ' ' && str[i - 1] != str[i])
			return (i);
		if (str[i + 1] != ' ' && str[i + 1] != str[i])
			return (i);
	}
	return (0);
}

int	needs_space(char *str)
{
	int	i;
	int	out;
	int	open;

	if (!str)
		return (0);
	i = 0;
	out = 0;
	open = 0;
	while (str[i])
	{
		open = open_state(open, str[i]);
		if (!open)
			out = check_character(str, i);
		if (out != 0)
			return (out);
		i++;
	}
	return (0);
}
