/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_process_subtoken.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:45:48 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/04 14:04:31 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "libft_bonus.h"
#include <stdlib.h>
#include <stdio.h>

static char	**set_strings(char *str, char **dst)
{
	int	state;
	int	i;
	int	j;

	i = 0;
	j = 0;
	state = 0;
	while (str[i])
	{
		state = quote_state(state, str[i]);
		if (!state && (str[i] == '\'' || str[i] == '\"'))
		{
			dst[j] = malloc(sizeof(char) * (i + 1));
			if (!dst[j])
			{
				free_double((void **)dst);
				return (NULL);
			}
			ft_strlcpy(dst[j++], str, (i + 2));
			str = str + i + 1;
			i = -1;
		}
		i++;
	}
	return (dst);
}

static t_list	*add_subtokens(t_list **list, char **strings)
{
	t_list	*new_list;
	t_token	*token;
	int		i;
	int		type;

	i = 0;
	type = 5;
	new_list = *list;
	token = new_list->content;
	free(token->string);
	token->string = strings[i];
	token->type = type;
	new_list = NULL;
	while (strings[i++])
	{
		if (!strings[i + 1])
			type = 6;
		ft_lstadd_back(&new_list, ft_lstnew(new_token(strings[i], type, -1)));
	}
	((t_list *)*list)->next = new_list;
	return (*list);
}

static t_list	*generate_subtokens(t_list **list, int count)
{
	t_list	*new_list;
	t_list	*aux;
	t_token	*token;
	char	**strings;

	new_list = *list;
	strings = malloc(sizeof(char *) * (count + 1));
	if (!strings)
		printf("Putada\n"); // Error: Not enough memory
	token = new_list->content;
	strings = set_strings(token->string, strings); // STRINGS ARE SUCCESSFULLY SAVED
	if (!strings)
		printf("Otra putada\n"); // Error: Not enough memory
	aux = new_list->next;
	new_list = add_subtokens(&new_list, strings); // TYPE IS NOT SAVED??? 
	free(strings);
	ft_lstadd_back(&new_list, aux);
	return (new_list);
}

static int	same_level_quotes(char *string)
{
	int	state;
	int	quotes;
	int	i;

	if (!ft_strchr(string, '\'') && !ft_strchr(string, '\"'))
		return (0);
	i = 0;
	quotes = 0;
	state = 0;
	while (string[i])
	{
		state = quote_state(state, string[i]);
		if (state == 1 && string[i] == '\'')
			quotes++;
		else if (state == 2 && string[i] == '\"')
			quotes++;
		i++;
	}
	if (quotes > 1)
		return (quotes);
	return (0);
}

t_list	*process_subtokens(t_list **token_list)
{
	t_list	*aux;
	t_token	*token;
	int		subtoken_count;

	aux = *token_list;
	while (42)
	{
		token = aux->content;
		if (token->type < 0)
		{
			subtoken_count = same_level_quotes(token->string);
			if (subtoken_count)
				aux = generate_subtokens(&aux, subtoken_count);
		}
		aux = aux->next;
		token = aux->content;
		if (!token->string)
			break ;
	}
	return (*token_list);
}
