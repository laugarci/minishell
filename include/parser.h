/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:42:45 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/26 15:40:44 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define CMD	0
# define EVAL	1
# define PIPE	2

typedef struct s_token
{
	char	*content;
	int		type;
	int		quotes;
	void	*next;
}			t_token;

char		*expand_evals(char *input, char *envp[]);
int			expansion_amount(char *input);
char		*find_eval(char *str, char *envp[]);

int			check_quote_state(char *input);
char		*remove_quotes(char *str);

#endif
