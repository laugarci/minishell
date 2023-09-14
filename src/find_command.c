/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 10:09:20 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/14 21:40:26 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"
#include "parser.h"
#include "libft_bonus.h"

#include <stdio.h>

char	*find_command(t_list *lst)
{
	size_t	total_length;
	t_token	*token;
	t_list	*current;
	int		i;
	char	*result;

	total_length = total_input_len(lst);
	result = malloc(sizeof(char) * (total_length + 1));
	if (!result)
		return (NULL); // Error: malloc
	current = lst;
	i = 0;
	while (current->next)
	{
		token = current->content;
		if ((token->type == 3 || token->type == 4))
			break ;
		if (i > 0)
			result[i++] = ' ';
		ft_strlcpy(result + i, token->string, total_length);
		i += ft_strlen(token->string);
		current = current->next;
	}
	result[total_length] = '\0';
	return (result);
}

char	*find_output(t_list *lst)
{
	t_list	*tmp;
	t_token	*token;
	char	*output;

	tmp = lst;
	token = tmp->content;
	output = NULL;
	while (tmp)
	{
		if (token->type == 3 || token->type == 4)
		{
			output = malloc(sizeof(char) * ft_strlen(token->string) + 1);
			if (!output)
				return (NULL); // Error: malloc
			ft_strlcpy(output, token->string, ft_strlen(token->string) + 1);
			tmp = tmp->next;
			token = tmp->content;
			if (token->type != 3 && token->type != 4)
				break ;
		}
		tmp = tmp->next;
		token = tmp->content;
	}
	return (output);
}
