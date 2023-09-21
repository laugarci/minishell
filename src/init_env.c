/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:21:07 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/21 13:52:38 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_bonus.h"
#include "minishell.h"
#include "minishell_defs.h"

static void	*free_var_and_return(t_env *var)
{
	free_var(var);
	return (NULL);
}

static void	*free_lst_envar_and_return(t_list *lst)
{
	ft_lstclear(&lst, (void *)free_var);
	return (NULL);
}

static t_list	*lst_oldpwd()
{
	t_env	*var;
	t_list	*out;

	var = new_env_var("OLDPWD");
	if (!var)
		return (NULL);
	out = ft_lstnew((void *)var);
	if (!out)
		return (free_var_and_return(var));
	return (out);
}

t_list	*set_env(char *envp[])
{
	t_list	*out;
	t_list	*aux;
	t_env	*var;
	int		flag;

	flag = 0;
	while (*envp)
	{
		var = new_env_var(*envp);
		if  (!var)
			return (free_var_and_return(var));
		aux = ft_lstnew((void *)var);
		if (!aux)
		{
			free_var(var);
			if (out)
				return (free_lst_envar_and_return(out));
		}
		if (!ft_strncmp(var->key, "OLDPWD\0", 7))
			flag++;
		ft_lstadd_back(&out, (void *)var);
		envp++;
	}
	if (!flag)
		return (out);
	aux = lst_oldpwd();
	if (!aux)
		return (free_lst_envar_and_return(out));
	ft_lstadd_back(&out, aux);
	return (out);
}
