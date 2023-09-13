/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:29:17 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/13 15:09:02 by laugarci         ###   ########.fr       */
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

//falta solucionar que si hay una redireccion > se haga tambien


char	*find_del(t_list *lst)
{
	char *del;
	t_token *token;

	token = lst->content;
	while(token->type != HERE_DOC)
	{
		lst = lst->next;
		token = lst->content;
	}
	del = malloc(sizeof(char) * ft_strlen(token->string) + 1);
	if (!del)
		return (NULL);
	ft_strlcpy(del, token->string, ft_strlen(token->string) + 1);
	return (del);
}

int	here_doc(t_list *lst, char **env)
{
	char	*del;
	t_token	*aux;
	char	*input;
	char	*command;
	t_list	*tmp;
	char	*text;

	text = NULL;
	del = find_del(lst);
	while (42)
	{	
		input = readline("heredoc> ");
		if (ft_strncmp(input, del, ft_strlen(del) + 1) == 0)
			break ;
		text = ft_strjoin(text, input);
		text = ft_strjoin(text, "\n");
		input = expand_evals(input, env);
	}
	if (count_list(lst) > 2)
	{	
		aux = lst->content;
		if (ft_strncmp(aux->string, "cat", 3) == 0)
			printf("%s", text);
		else
		{
		command = malloc(sizeof(char) * ft_strlen(aux->string) + 1);
		if (!command)
			return (-1);
		ft_strlcpy(command, aux->string, ft_strlen(aux->string) + 1);
		tmp = save_tokens(command);
		write(1, text, ft_strlen(text));
		exec_commands(tmp, env);
		}
	}
	return (0);
}
