/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:30:35 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/14 19:13:44 by laugarci         ###   ########.fr       */
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
	t_list	*aux;
	int		i;
	int		flag;

	aux = lst;
	flag = 0;
	i = count_list(lst);
	if (i == 2)
		printf("\n");
	else
	{
		i = 1;
		while(i < (count_list(lst) - 1))
		{
			aux = aux->next;
			token = aux->content;
			if (ft_strncmp(token->string, "-n", 2) == 0)
				flag = 1;
			aux = aux->next;
			token = aux->content;
			printf("%s", token->string);
			i++;
		}
		if (flag == 0)
			printf("\n");
	}
	return (0);
}
