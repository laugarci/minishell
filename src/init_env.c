/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:21:07 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/20 18:47:03 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_defs.h"

t_list	*set_env(char *envp[])
{
	t_list	*out;
	t_env	*var;
	int		i;

	i = 0;
	while (envp[i])
	{
		var = new_env_var(envp[i]);
		if (!var)
		{
			ft_lstclear(&out, (void *)free_var());
			return (NULL);
		}
	}
}
