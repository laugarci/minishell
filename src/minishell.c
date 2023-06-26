/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:52:21 by laugarci          #+#    #+#             */
/*   Updated: 2023/06/26 16:26:35 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "libft.h"

int main(int argc, char *argv[], char *envp[])
{
	char *input;
	
	if (argc > 1)
		exit(1);
	argv = NULL;
	envp = NULL;
	while (1)
	{
		input = readline("minishell > ");
		free(input);
	}
	return (0);
}
