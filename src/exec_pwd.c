/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:28:34 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/04 12:04:59 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "libft_bonus.h"
#include "parser.h"

int	exec_pwd()
{
    char *cwd;

    cwd = getcwd(NULL, 0);

    if (cwd != NULL)
	{
        printf("%s\n", cwd);
        free(cwd); 
    }
    return (0);
}
