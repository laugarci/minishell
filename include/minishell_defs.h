/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_defs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:00:09 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/19 18:30:11 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFS_H
# define MINISHELL_DEFS_H

# define PIPE			0
# define INFILE			1
# define HERE_DOC		2
# define APPEND			3
# define TRUNC			4
# define TOKEN_APPEND	5
# define TOKEND			6

# define STATE_READ		0
# define STATE_HDOC		1
# define STATE_EXEC		2

# define MODE_RETURN	-1
# define MODE_UNSET		0
# define MODE_SET		1

# include "libft_defs.h"

// If the variable has no = then value = NULL, if it has = then value is ""
typedef struct	s_env
{
	char	*key;
	char	*value;
}			t_env;

typedef struct s_token
{
	char	*string;
	int		type;
	int		quotes;
}			t_token;

#endif
