/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 21:05:30 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/24 15:45:15 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "libft.h"
#include "minishell.h"
#include "libft_bonus.h"
#include "parser.h"

int	exec_cd(t_list *lst)
{
	t_token	*token;
	t_list	*tmp;
	int		i;
	
	i = count_list(lst);
	tmp = lst->next;
	token = tmp->content;
	if (i == 2)
	{
		if (chdir(getenv("HOME")) == 1)
			return (1);
	}
	else if (access((token->string), F_OK) != -1)
	{
		if (access((token->string), R_OK) != -1)
		{
			if (chdir(token->string) == -1)
			{
				printf("cd %s: No such file or directory", token->string);
				return (1);
			}
		}
		else
		{
			printf("minishell: cd: %s: Permission denied\n", token->string);
			return (1);
		}
	}
	else
	{
		printf("cd %s: No such file or directory\n", token->string);
		return (1);
	}
	return (0);
}
