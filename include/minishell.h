/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 11:32:21 by ffornes-          #+#    #+#             */
/*   Updated: 2023/08/17 10:33:03 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft_defs.h"

char		*get_path(char *cmd, char **envp);

char		*here_doc(char **input, char *envp[]);

void		put_error(char *str, int error_id);

int			exec_commands(t_list *lst, char **env);

int			exec_commands_wf(t_list *lst, char **env, int flags);

int			exec_commands_other(char *space_pos, char *input, char **env);

int			cmp_commands(t_list *lst, char **env);

int			exec_cd(t_list *lst);

int			is_type(t_list *lst, int type);

int			count_chars(t_list *lst);

void		exec_pipes(char **env, int num_pipes, char *command);

int			count_args(t_list *lst);

char		*find_command(t_list *lst);

char		*find_output(t_list *lst);

int			exec_redirect(t_list *lst);

char		*ft_strtok(char *str, const char *del);

int			count_list(t_list *lst);

int			total_input_len(t_list *lst);

#endif
