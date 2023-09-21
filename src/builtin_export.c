/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 18:22:49 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/21 20:11:19 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "libft_bonus.h"
#include "minishell.h"

#include <stdio.h>

static int  print_export(t_list *env_lst)
{
    t_env   *var;
    char    *str;

    while (env_lst)
    {
        var = env_lst->content;
        printf("declare -x %s", var->key);
		if (var->value)
		{
    	    str = var->value;
    	    if (*str == '=')
    	    {
    	        str++;
    	        if (str)
    	            printf("=\"%s\"", str);
    	        else
    	            printf("=\"\"");
    	    }
		}
   	    printf("\n");
		env_lst = env_lst->next;
    }
    return (0);
}

static int	add_var_to_env(t_env *var, t_list **env_lst)
{
	t_list	*lst;
	t_env	*env_var;

	lst = *env_lst;
	while (lst)
	{
		env_var = lst->content;
		if (!ft_strncmp(env_var->key, var->key, ft_strlen(var->key)))
		{
			if (env_var->value)
				free(env_var->value);
			env_var->value = var->value;
			free(var->key);
			free(var);
			return (0);
		}
		lst = lst->next;
	}
	return (1);
}

int	builtin_export(t_list *tkn_lst, t_list **env_lst, char **env)
{
    t_list  *lst;
	t_list	*aux;
    t_token *token;
	t_env	*var;

    lst = *env_lst;
	tkn_lst = tkn_lst->next;
    token = tkn_lst->content;
	if (!token || (token->type >= 0 || !token->string))
        return (print_export(lst));
	var = new_env_var(token->string);
	if (!var)
		return (12);
	if (add_var_to_env(var, env_lst))
	{
		aux = ft_lstnew((void *)var);
		if (!aux)
		{
			free_var(var);
			return (12);
		}
		ft_lstadd_back(env_lst, aux);
	}
	return (0);
	(void)env;
}
