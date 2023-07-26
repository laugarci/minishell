/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:42:45 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/26 17:33:58 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define CMD	0
# define EVAL	1
# define PIPE	2

#include "libft_defs.h"

typedef struct s_token
{
	char	*string;
	int		type;
	int		quotes;
}			t_token;

char		*expand_evals(char *input, char *envp[]);
int			expansion_amount(char *input);
char		*find_eval(char *str, char *envp[]);

int			check_quote_state(char *input);
char		*remove_quotes(char *str);

t_token		*new_token(char *string, int type, int quotes);
t_list		*save_tokens(char *input);

int			double_charp_size(char **var);

#endif
