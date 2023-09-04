/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:29:17 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/04 10:40:16 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "libft_bonus.h"
#include "parser.h"
#include <readline/readline.h>
#include <readline/history.h>

int	here_doc(t_list *lst)
{
	char *del;
	t_token *aux;
	char *input;
	
	lst = lst->next;
	aux = lst->content;
	del = malloc(sizeof(char) * ft_strlen(aux->string) + 1);
	ft_strlcpy(del, aux->string, ft_strlen(aux->string) + 1);
	while (42)
	{
		input = readline("heredoc> ");
		if (ft_strncmp(input, del, ft_strlen(del) + 1) == 0)
			break ;
	}
 	return (0);
}
