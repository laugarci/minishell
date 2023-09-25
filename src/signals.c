/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:24:45 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/24 17:32:39 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "minishell_defs.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "termios.h"

int	set_or_return_state(int mode, int value)
{
	static int	state;

	if (mode == MODE_SET)
		state = value;
	return (state);
}

static void	state_read(int sig, siginfo_t *data, void *n_data)
{
	(void) data;
	(void) n_data;
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		set_or_return_exit_status(MODE_SET, 1);
	}
	else if (sig == SIGQUIT)
		rl_redisplay();
	return ;
}

static void	state_hdoc(int sig, siginfo_t *data, void *n_data)
{
	(void) data;
	(void) n_data;
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 1);
		exit(1);
	}
	else if (sig == SIGQUIT)
		rl_redisplay();
	return ;
}

static void	state_exec(int sig, siginfo_t *data, void *n_data)
{
	(void) data;
	(void) n_data;
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 1);
		return ;
	}
	else if (sig == SIGQUIT)
		rl_redisplay();
	return ;
}

int	*signal_handler(void)
{
	struct sigaction	signal;
	int					state;

	signal.sa_flags = SA_RESTART;
	sigemptyset(&signal.sa_mask);
	state = set_or_return_state(MODE_RETURN, -1);
	if (state == STATE_READ)
		signal.sa_sigaction = state_read;
	else if (state == STATE_HDOC)
		signal.sa_sigaction = state_hdoc;
	else if (state == STATE_EXEC)
		signal.sa_sigaction = state_exec;
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
	return (0);
}
