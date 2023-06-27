/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:01:51 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/27 13:12:52 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	put_error(char *str, int error_id)
{
	char	*aux;

	aux = NULL;
	if (error_id == 127)
		aux = ft_strjoin(str, ": command not found\n");
	else if (error_id == 128)
		aux = ft_strjoin(str, ": unable to execute command\n");	
	ft_putstr_fd(aux, 2);
	free(aux);
}