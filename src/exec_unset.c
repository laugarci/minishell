
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "libft_bonus.h"
#include "parser.h"

int	exec_unset(t_list *lst, char **env)
{
	t_token *token;
	t_list	*aux;
	int	i;
	int	j;

	aux = lst->next;
	token = aux->content;
	i = 0;

	while(env[i])
	{
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
		i++;
	}
	return (1); // Error: variable no encontrada
}
