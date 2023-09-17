/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:24:45 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/17 19:56:16 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "minishell_defs.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

// Using WRITE > PRINTF since PRINTF can crash when used in a signal handler

static void	state_read(int sig, siginfo_t *data, void *n_data)
{
	(void) data;
	(void) n_data;
	
	if (sig == SIGINT)
	{
		//ft_putstr_fd("Recieved: SIGINT in STATE=READ", 1);
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("minishell$ ", 1);
//		ft_putstr_fd("\n", 1);
//		rl_reset_line_state(); 
	}
	else if (sig == SIGQUIT)
		//printf("Recieved: SIGQUIT in STATE=READ\n");
	return ;
}

static void	state_hdoc(int sig, siginfo_t *data, void *n_data)
{
	(void) data;
	(void) n_data;

	if (sig == SIGINT)
		printf("Recieved: SIGINT in STATE=HDOC\n");
	else if (sig == SIGQUIT)
		printf("Recieved: SIGQUIT in STATE=HDOC\n");
	return ;
}

static void	state_exec(int sig, siginfo_t *data, void *n_data)
{
	(void) data;
	(void) n_data;

	if (sig == SIGINT)
		printf("Recieved: SIGINT in STATE=EXEC\n");
	else if (sig == SIGQUIT)
		printf("Recieved: SIGQUIT in STATE=EXEC\n");
	return ;
}

int	*signal_handler(int	*state, int *exit_status)
{
	struct sigaction	signal;
	
	signal.sa_flags = SA_RESTART;
	sigemptyset(&signal.sa_mask);
	if (*state == STATE_READ)
		signal.sa_sigaction = state_read;
	else if (*state == STATE_HDOC)
		signal.sa_sigaction = state_hdoc;
	else if (*state == STATE_EXEC)
		signal.sa_sigaction = state_exec;
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
	*exit_status = 0;
	return (0);
}
