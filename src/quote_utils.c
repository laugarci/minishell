/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:14:09 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/31 17:15:14 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	open_state(int state, char c)
{
	if (!state && c == '\'')
		return (1);
	else if (!state && c == '\"')
		return (2);
	else if ((state == 1 && c == '\'') || (state == 2 && c == '\"'))
		return (0);
	return (state);
}
