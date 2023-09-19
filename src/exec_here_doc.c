/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:29:17 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/19 12:39:22 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "minishell_defs.h"
#include "libft_bonus.h"
#include "parser.h"
#include <readline/readline.h>
#include <readline/history.h>

//falta solucionar que si hay una redireccion > se haga tambien

int	find_cat(t_list *aux)
{
	t_token *token;
	int		i;
	t_list	*tmp;

	tmp = aux;
	token = tmp->content;
	i = 0;
	if (token->type != 2)
	{
		while(token->type != 2)
		{
			tmp = tmp->next;
			token = tmp->content;
			if (ft_strncmp(token->string, "cat\0", 4) == 0)
			{
				tmp = tmp->next;
				token = tmp->content;
				if (token->type == 2)
				{
					i = 1;
					break ;
				}
			}
		}
	}
	return (i);
}

char	*find_del(t_list *lst)
{
	char *del;
	t_token *token;

	token = lst->content;
	if (token->type != HERE_DOC)
	{
		while(token->type != HERE_DOC)
		{
			lst = lst->next;
			token = lst->content;
		}
	}
	del = malloc(sizeof(char) * ft_strlen(token->string) + 1);
	if (!del)
		return (NULL);
	ft_strlcpy(del, token->string, ft_strlen(token->string) + 1);
	return (del);
}

int	here_doc(t_list *lst)
{
	char	*del;
	char	*input;
	char	*text;
	int		flag;
	t_token *token;

	flag = 0;
	text = NULL;
	del = find_del(lst);
	set_or_return_state(MODE_SET, STATE_HDOC);
	signal_handler();
	while (42)
	{
		input = readline("heredoc> ");
		if (ft_strncmp(input, del, ft_strlen(del) + 1) == 0)
			break ;
		text = ft_strjoin(text, input);
		text = ft_strjoin(text, "\n");
//		input = expand_evals(input, env);
	}
	if (count_list(lst) > 2)
	{
		token = lst->content;
		flag = find_cat(lst);
		if (flag == 1 || ft_strncmp(token->string, "cat\0", 3) == 0)
		{
			if ((is_type(lst, 3) || is_type(lst, 4)))
				exec_redirect(lst);
			write(1, text, ft_strlen(text));
			exit(1);
		}
	}
	//to solve >> ls -a | wc -l | cat -e > a | cat << hola > b
	return (0);
}
