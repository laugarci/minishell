/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:42:45 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/15 10:24:09 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define PIPE			0
# define INFILE			1
# define HERE_DOC		2
# define APPEND			3
# define TRUNC			4
# define TOKEN_APPEND	5
# define TOKEND			6

# include "libft_defs.h"

typedef struct s_token
{
	char	*string;
	int		type;
	int		quotes;
}			t_token;

int			parse_input(char *str, char *envp[], t_list **token_list, int *exit_status);

char		*clean_input(char *input);
int			needs_space(char *str);
char		**split_input(char *input);

int			syntax_error_check(t_list *lst);

char		*expand_evals(char *input, char *envp[], int *exit_status);
int			expansion_amount(char *input);
int			find_eval(char *str, char *envp[], char **dst);

int			remove_quotes(t_token **token);
int			quote_state(int state, char c);

t_token		*new_token(char *string, int type, int quotes);
t_list		*save_tokens(char *input);
int			process_tokens(t_list **token_list, char *envp[], int *exit_status);
int			process_subtokens(t_list **token_list);
int			count_subtokens(char *string);
int			join_subtoken(t_list **token_list);
t_list		*set_type(t_list **token_list);
void		remove_duplicates(t_list **token_list);
void		free_token(void *var);

void		print_tokens(t_list *lst); // DEBUG

#endif
