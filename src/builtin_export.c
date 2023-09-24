/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 18:22:49 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/24 17:46:10 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "libft_bonus.h"
#include "minishell.h"
#include "minishell_defs.h"

#include <stdio.h>

static int	print_export(t_list *env_lst)
{
	t_env	*var;
	char	*str;

	while (env_lst)
	{
		var = env_lst->content;
		printf("declare -x %s", var->key);
		if (var->value)
		{
			str = var->value;
			if (*str == '=')
			{
				str++;
				if (str)
					printf("=\"%s\"", str);
				else
					printf("=\"\"");
			}
		}
		printf("\n");
		env_lst = env_lst->next;
	}
	return (0);
}

static int	free_key_and_return(t_env *var)
{
	if (var->key)
		free(var->key);
	free(var);
	return (0);
}

static int	add_var_to_env(t_env *var, t_list **env_lst, char *str)
{
	t_list	*lst;
	t_env	*env_var;
	char	*aux;

	lst = *env_lst;
	aux = NULL;
	while (lst)
	{
		env_var = lst->content;
		if (!ft_strncmp(env_var->key, var->key, ft_strlen(var->key)))
		{
			if (!var->value)
				return (free_key_and_return(var));
			if (env_var->value)
				aux = env_var->value;
			env_var = check_flag(env_var, var, str);
			if (aux)
				free(aux);
			return (free_key_and_return(var));
		}
		lst = lst->next;
	}
	return (1);
}

static int	is_valid_input(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i] && str[i] != '=')
	{
		if (!i && ft_isdigit(str[i]))
			flag++;
		else if (!ft_isalnum(str[i]) && str[i] != '_')
			flag++;
		if (flag)
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("\': not a valid identifier\n", 2);
			set_or_return_exit_status(MODE_SET, 1);
			return (0);
		}
		i++;
	}
	return (1);
}

int	builtin_export(t_list *tkn_lst, t_list **env_lst)
{
	t_list	*lst;
	t_list	*aux;
	t_token	*token;
	t_env	*var;

	lst = *env_lst;
	tkn_lst = tkn_lst->next;
	token = tkn_lst->content;
	if (!token || (token->type >= 0 || !token->string))
		return (print_export(lst));
	if (!is_valid_input(token->string))
		return (1);
	var = new_env_var(token->string);
	if (!var)
		return (12);
	if (add_var_to_env(var, env_lst, token->string))
	{
		aux = ft_lstnew((void *)var);
		if (!aux)
			return (free_var_return_value(var, 12));
		ft_lstadd_back(env_lst, aux);
	}
	return (0);
}
