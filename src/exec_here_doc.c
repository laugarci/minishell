/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:29:17 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/04 18:05:04 by laugarci         ###   ########.fr       */
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

//segfault en casos en los que se inicia con << y no con comando/palabra

int	here_doc(t_list *lst, char **env)
{
	char	*del;
	t_token	*aux;
	char	*input;
	char	*command;
	t_list	*tmp;

	aux = lst->content;
	command = malloc(sizeof(char) * ft_strlen(aux->string + 1));
	ft_strlcpy(command, aux->string, ft_strlen(aux->string) + 1);
	lst = lst->next;
	aux = lst->content;
	del = malloc(sizeof(char) * ft_strlen(aux->string) + 1);
	ft_strlcpy(del, aux->string, ft_strlen(aux->string) + 1);
	while (42)
	{
		input = readline("heredoc> ");
//		input = expand_evals(input, env);
		if (ft_strncmp(input, del, ft_strlen(del) + 1) == 0)
			break ;
	}
	tmp = save_tokens(command);
	exec_commands(tmp, env);
	return (0);
}
