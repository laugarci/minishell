/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:01:51 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/24 13:11:13 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	put_error(char *str, int error_id)
{
	char	*aux;

	aux = NULL;
	if (error_id == 42)
		aux = ft_strjoin(str, ": found forbidden character: `\\\'\n");
	else if (error_id == 43)
		aux = ft_strjoin(str, ": found forbidden character: `;\'\n");
	else if (error_id == 44)
		aux = ft_strjoin(str, ": error near unexpected token `\'\'\n");
	else if (error_id == 45)
		aux = ft_strjoin(str, ": error near unexpected token `\"\'\n");
	else if (error_id == 127)
		aux = ft_strjoin(str, ": No such file or directory\n");
	else if (error_id == 128)
		aux = ft_strjoin(str, ": unable to execute command XD\n");
	ft_putstr_fd(aux, 2);
	free(aux);
}
