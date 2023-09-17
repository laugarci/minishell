/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:24:45 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/17 17:47:48 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_defs.h"
#include <signal.h>
#include <readline/readline.h>

#include <stdio.h>

static void	state_read(int signal)
{
	if (signal == SIGINT) // ctrl-C
	{
		rl_redisplay();
		printf("\n");
	}
	else if (signal == SIGQUIT) // ctrl-\ *
		return ;
}

int	*signal_handler(int	*state, int *exit_status)
{
	if (*state == STATE_READ)
	{
		printf("State read\n");
		signal(SIGINT, (void *)state_read);
		signal(SIGQUIT, (void *)state_read);
		signal(SIGTERM, (void  *)state_read);
	}
	else if (*state == STATE_HDOC)
		printf("State here_doc\n");
	else if (*state == STATE_EXEC)
		printf("State exec\n");

	*exit_status = 0;
	return (0);
}
