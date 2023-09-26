/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:52:54 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/26 15:22:25 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "minishell_defs.h"
#include "parser.h"
#include <limits.h>
#include <stdlib.h>

static long long	check_limits(unsigned long long j, int i)
{
	long long			out;

	if (i)
		j -= 1;
	if (j > LONG_MAX)
		return (0);
	out = (long long)j;
	if (i)
	{
		if (out == 0)
		{
			out += 1;
			out *= -1;
		}
		else
		{
			out *= -1;
			out += 1;
		}
	}
	return (out);
}

long long	ft_atoll(const char *str)
{
	int					i;
	unsigned long long	j;

	i = 0;
	j = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			i++;
		if (*(str + 1) == '+' || *(str + 1) == '-')
			return (0);
		str++;
	}
	while (ft_isdigit(*str))
	{
		j = (j * 10) + (*str - '0');
		str++;
	}
	return (check_limits(j, i));
}

static int	check_digits(char *input)
{
	if (*input == '-' || *input == '+')
		input++;
	while (ft_isdigit(*input))
		input++;
	if (*input && !ft_isdigit(*input))
		return (1);
	return (0);
}

void	builtin_exit(char *input)
{
	long long	out;

	if (!input)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	out = ft_atoll(input);
	while (*input == '0')
		input++;
	if (check_digits(input) || (!out && *input != '\0'))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(input, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	ft_putstr_fd("exit\n", 1);
	while (out > 255)
		out -= (out / 255) * 256;
	exit(out);
}

void	exit_check(t_list *lst)
{
	t_token	*token;
	t_token	*aux;

	token = lst->content;
	if (!ft_strncmp(token->string, "exit\0", 5))
	{
		lst = lst->next;
		token = lst->content;
		if (token->string)
		{
			lst = lst->next;
			aux = lst->content;
			if (aux->string)
			{
				ft_putstr_fd("minishell: exit: too many arguments\n", 2);
				set_or_return_exit_status(MODE_SET, 1);
			}
			else
				builtin_exit(token->string);
		}
		else
			builtin_exit(NULL);
	}
}
