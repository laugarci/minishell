/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:30:35 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/04 17:54:08 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "libft_bonus.h"
#include "parser.h"

int	exec_echo(t_list *lst)
{
	t_token	*token;
	char	*var_name;
	char	*env_var;
	int		i;

	i = count_list(lst);
	if (i == 2)
		printf("\n");
	else
	{
		lst = lst->next;
		token = lst->content;
		if (ft_strncmp(token->string, "$", 1) == 0)
		{
			var_name = token->string + 1;
			env_var = getenv(var_name);
			if (env_var != NULL)
				printf("%s\n", env_var);
			else
				printf("\n");
		}
		else
			printf("%s\n", token->string);
	}
	return (0);
}
