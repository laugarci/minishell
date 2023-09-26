/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:09:21 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/26 11:29:58 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "minishell_defs.h"
#include "parser.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static int	setup_data(t_list *lst, t_data *data)
{
	int	i;

	i = 0;
	data->hd_total = type_count(lst, HERE_DOC);
	if (data->hd_total)
	{
		data->hdoc_fds = malloc(sizeof(int) * data->hd_total);
		if (!data->hdoc_fds)
			return (12);
		while (i < data->hd_total)
		{
			data->hdoc_fds[i] = here_doc(lst, i);
			if (data->hdoc_fds[i] < 0)
			{
				free(data->hdoc_fds);
				return (1);
			}
			i++;
		}
	}
	return (0);
}

int	start_execution(t_list *lst, t_list **env_lst, char **env)
{
	int			process_count;
	t_data		data;
	int			err;

	init_data(&data);
	if (!data.read_pipe_fds || !data.next_read_fd)
		return (12);
	process_count = type_count(lst, PIPE);
	data.pipe_count = process_count;
	if (!process_count)
		process_count = 1;
	err = setup_data(lst, &data);
	if (err > 0)
		return (err);
	set_or_return_state(MODE_SET, STATE_EXEC);
	signal_display(MODE_SET);
	signal_handler();
	execution(lst, env_lst, &data, env);
	return (0);
}