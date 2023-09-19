/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_defs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:00:09 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/19 17:51:04 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFS_H
# define MINISHELL_DEFS_H

# define STATE_READ		0
# define STATE_HDOC		1
# define STATE_EXEC		2

# define MODE_RETURN	-1
# define MODE_UNSET		0
# define MODE_SET		1

# include "libft_defs.h"

typedef struct s_data
{
	char	**env;
	t_list	*export_list;
}			t_data;

#endif
