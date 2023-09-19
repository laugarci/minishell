/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:39:50 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/18 15:52:18 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "minishell_defs.h"
#include "parser.h"

void	print_error(char *error_message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error_message, 2);
}

int	print_and_return(int error_id)
{
	if (error_id == 12)
		print_error("Cannot allocate memory\n");
	else if (error_id == 126)
		print_error("Unable to execute command\n");
	else if (error_id == 127)
		print_error("No such file or directory\n");
	return (error_id);
}
