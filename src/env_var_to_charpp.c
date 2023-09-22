/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_charpp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:10:10 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/21 19:52:47 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_bonus.h"
#include "minishell_defs.h"
#include <stdlib.h>

#include <stdio.h>

static void	*free_and_return(char **out)
{
	free_double((void **)out);
	return (NULL);
}

char	**envlst_to_charpp(t_list *lst)
{
	t_env	*var;
	char	**out;
	int		i;

	if (!lst)
		return (NULL);
	out = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!out)
		return (NULL);
	i = 0;
	while (lst)
	{
		var = lst->content;
		if (var->value)
		{
			out[i] = ft_strjoin(var->key, var->value);
			if (!out[i++])
				return (free_and_return(out));
		}
		else
			out[i] = ft_strdup(var->key);
		lst = lst->next;
	}
	out[i] = NULL;
	return (out);
}
