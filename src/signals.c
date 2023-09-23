/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:24:45 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/23 12:11:48 by laugarci         ###   ########.fr       */
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

void	signal_display(int mode)
{
	struct termios	tc;

	tcgetattr(0, &tc);
	tc.c_lflag &= ~ECHOCTL;
	if (mode)
		tc.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &tc);
}

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
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
	return (0);
}
