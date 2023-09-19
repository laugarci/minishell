/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:05:03 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/18 18:29:23 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_defs.h"

int	set_or_return_exit_status(int mode, int value)
{
	static int	exit_status;

	if (mode == MODE_SET)
		exit_status = value;
	return (exit_status);
}