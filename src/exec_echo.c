/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:30:35 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/15 18:02:38 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "libft_bonus.h"
#include "parser.h"

void	print_echo(t_list *aux, t_list *lst, int flag)
{
	t_token	*token;
	int		i;

	i = 1;
	token = aux->content;
	while (i < (count_list(lst) - 1 - flag))
	{
		printf("%s", token->string);
		if (i < (count_list(lst) - 2 - flag))
			printf(" ");
		aux = aux->next;
		token = aux->content;
		i++;
	}
	if (flag == 0)
		printf("\n");
}

int	exec_echo(t_list *lst)
{
	t_token	*token;
	t_list	*aux;
	int		i;
	int		flag;
	
	write(1, "llega\n", 6);
	print_tokens(lst);
	aux = lst;
	flag = 0;
	i = count_list(lst);
	if (i == 2)
	{
		printf("\n");
		return (0);
	}
	aux = aux->next;
	token = aux->content;
	if (ft_strncmp(token->string, "-n", 2) == 0)
	{
		flag = 1;
		aux = aux->next;
	}
	print_echo(aux, lst, flag);
	return (0);
}
