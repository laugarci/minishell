/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:42:45 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/26 15:23:17 by ffornes-         ###   ########.fr       */
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

#endif
