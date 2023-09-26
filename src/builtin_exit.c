/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:52:54 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/26 23:47:19 by laugarci         ###   ########.fr       */
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

void	put_numeric_error(char *input)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(input, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
}

static int	check_digits(char *input)
{
	int	i;

	while (*input == ' ')
		input++;
	if (!ft_strncmp(input, "-18446744073709551617\0", 22))
		put_numeric_error(input);
	if (*input == '-' || *input == '+')
		input++;
	if (!input || !*input)
		return (1);
	while (*input == '0')
		input++;
	if (!input || !*input)
	{
		ft_putstr_fd("exit\n", 0);
		exit(0);
	}
	i = 0;
	while (ft_isdigit(*input))
	{
		i++;
		input++;
		if (i > 20)
			put_numeric_error(input - i);
	}
	while (*input == ' ')
		input++;
	if (*input && !ft_isdigit(*input))
		return (1);
	return (0);
}

void	builtin_exit(char *input)
{
	long long	out;

	if (!input)
		exit(0);
	out = ft_atoll(input);
	if (check_digits(input) || (!out && *input != '\0'))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(input, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	if (out > 0)
		while (out > 255)
			out -= (out / 255) * 256;
	else if (out < 0)
	{
		while (out < -255)
			out += (out / 255) * 256 * -1;
		if (out == -1)
			out = 255;
		else
			out -= 2;
	}
	ft_putstr_fd("exit\n", 0);
	exit(out);
}

void	exit_check(t_list *lst, int *err)
{
	t_token	*token;
	t_token	*aux;

	token = lst->content;
	if (!ft_strncmp(token->string, "exit\0", 5))
	{
		lst = lst->next;
		token = lst->content;
		if (token->string && *token->string)
		{
			lst = lst->next;
			aux = lst->content;
			if (aux->string && aux->type < 0)
			{
				if (!ft_isdigit(*token->string))
					builtin_exit(token->string);
				else
				{
					ft_putstr_fd("exit\n", 0);
					ft_putstr_fd("minishell: exit: too many arguments\n", 2);
					set_or_return_exit_status(MODE_SET, 1);
					*err = 1;
					return ;
				}
			}
			else
				builtin_exit(token->string);
		}
		else if (token->string && !*token->string)
		{
			ft_putstr_fd("exit\n", 0);
			ft_putstr_fd("minishell: exit: : numeric argument required\n", 2);
			builtin_exit("255");
		}
		builtin_exit(ft_itoa(set_or_return_exit_status(MODE_RETURN, -1)));
	}
}
