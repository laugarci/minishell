
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "libft_bonus.h"
#include "parser.h"

static int	exec_unset_util(char **env, t_token *token, int i)
{
	int	j;

	j = 0;
	if (ft_strncmp(env[i], token->string, ft_strlen(token->string)) == 0 &&
		env[i][ft_strlen(token->string)] == '=')
	{
		free(env[i]);
		j = i;
		while(env[j])
		{
			env[j] = env[j + 1];
			j++;
		}
		return (0);
	}
	return (1);
}

int	exec_unset(t_list *lst, char **env)
{
	t_token *token;
	t_list	*aux;
	int	i;
	int	out;

	if (!lst->next)
		return (0);
	aux = lst->next;
	if (!aux->content)
		return (0);
	token = aux->content;
	if (!token->string)
		return (0);
	i = 0;
	out = 0;
	while(env[i])
		out = exec_unset_util(env, token, i++);
	return (out);
}
