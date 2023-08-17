/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:26:31 by laugarci          #+#    #+#             */
/*   Updated: 2023/08/17 09:56:49 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "parser.h"
#include "libft_bonus.h"

int	is_type(t_list *lst, int type)
{
	t_token	*aux;
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		aux = tmp->content;
		if (aux->type == type)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	count_chars(t_list *lst)
{
	int		c;
	t_list	*tmp;
	t_token	*aux;

	c = 0;
	tmp = lst;
	while (tmp)
	{
		aux = tmp->content;
		if (aux->type == PIPE)
			c++;
		tmp = tmp->next;
	}
	return (c);
}

int	total_input_len(t_list *lst)
{
	t_list	*current;
	t_token	*token;
	int		total_length;

	current = lst;
	total_length = 0;
	while (current->next)
	{
		token = current->content;
		total_length += ft_strlen(token->string);
		current = current->next;
	}
	total_length = total_length + (count_list(lst));
	return (total_length);
}

int	count_list(t_list *lst)
{
	int		i;
	t_list	*tmp;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	*ft_strtok(char *str, const char *del)
{
	static char	*token;
	char		*start;
	int			i;
	int			j;
	char		*final;

	i = 0;
	if (str != NULL)
		token = str;
	if (token == NULL || *token == '\0')
		return (NULL);
	while (token[i])
	{
		j = 0;
		while (del[++j])
		{
			if (token[i] == del[j])
			{
				i++;
				break ;
			}
		}
		if (del[j] == '\0')
			break ;
	}
	if (token[i] == '\0')
		return (NULL);
	start = &token[i];
	while (token[++i])
	{
		j = 0;
		while (del[j])
		{
			if (token[i] == del[j])
			{
				token[i] = '\0';
				i++;
				token += i;
				final = ft_strtrim(start, " ");
				return (final);
			}
			j++;
		}
	}
	token += i;
	final = ft_strtrim(start, " ");
	return (final);
}
