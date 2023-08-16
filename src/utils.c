/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:26:31 by laugarci          #+#    #+#             */
/*   Updated: 2023/08/16 16:20:26 by laugarci         ###   ########.fr       */
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
	while (token[i] != '\0')
	{
		j = 0;
		while (del[j] != '\0')
		{
			if (token[i] == del[j])
			{
				i++;
				break ;
			}
			j++;
		}
		if (del[j] == '\0')
			break ;
	}
	if (token[i] == '\0')
		return (NULL);
	start = &token[i];
	while (token[i] != '\0')
	{
		j = 0;
		while (del[j] != '\0')
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
		i++;
	}
	token += i;
	final = ft_strtrim(start, " ");
	return (final);
}
