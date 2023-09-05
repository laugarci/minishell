/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:30:35 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/05 14:27:07 by laugarci         ###   ########.fr       */
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

	aux = lst;
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
			printf("%s ", token->string);
			i++;
		}
		printf("\n");
	}
	return (0);
}
