/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:48:17 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/22 18:59:37 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "libft_bonus.h"
#include "parser.h"

static void	builtin_unset_util(t_list **previous, t_list *var_lst, \
			t_list **env_lst)
{
	t_list	*aux;

	aux = *previous;
	if (aux)
	{
		aux->next = var_lst->next;
		var_lst->next = NULL;
	}
	else
		*env_lst = var_lst->next;
	ft_lstclear(&var_lst, (void *)free_var);
}

int	builtin_unset(t_list *lst, t_list **env_lst)
{
	t_token	*token;
	t_list	*aux;
	t_list	*previous;
	t_list	*var_lst;
	t_env	*var;

	aux = lst->next;
	token = aux->content;
	if (!lst->next || !aux->content || !token->string)
		return (0);
	var_lst = *env_lst;
	previous = NULL;
	while (var_lst)
	{
		var = var_lst->content;
		if (!ft_strncmp(var->key, token->string, ft_strlen(token->string)))
		{
			builtin_unset_util(&previous, var_lst, env_lst);
			break ;
		}
		previous = var_lst;
		var_lst = var_lst->next;
	}
	return (0);
}
