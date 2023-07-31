/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:42:45 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/31 17:15:58 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define PIPE		0
# define INFILE		1
# define HERE_DOC	2
# define O_APPEND	3
# define O_TRUNC	4

#include "libft_defs.h"

typedef struct s_token
{
	char	*string;
	int		type;
	int		quotes;
}			t_token;

int			clean_input(char **input);

char		*expand_evals(char *input, char *envp[]);
int			expansion_amount(char *input);
char		*find_eval(char *str, char *envp[]);

int			check_quote_state(char *input);
char		*remove_quotes(char *str);
int			open_state(int state, char c);

t_token		*new_token(char *string, int type, int quotes);
char		**token_split(char *input);
t_list		*save_tokens(char *input);
void		process_tokens(t_list **token_list);

int			double_charp_size(char **var);

#endif
