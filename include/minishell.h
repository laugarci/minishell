/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 11:32:21 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/04 15:58:42 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft_defs.h"
# include "parser.h"
#include "libft_defs.h"
#include "minishell_defs.h"

char		*get_path(char *cmd, char **envp);

void		put_error(char *str, int error_id);

int			exec_commands(t_list *lst, char **env);

int			exec_commands_wf(t_list *lst, char **env, int flags);

int			exec_commands_other(char *space_pos, char *input, char **env);

int			cmp_commands(t_list *lst, char **env);

int			exec_cd(t_list *lst);

int			is_type(t_list *lst, int type);

int			count_chars(t_list *lst);

void		exec_pipes(char **env, int num_pipes, char *command, t_list *lst);

int			count_args(t_list *lst);

char		*find_command(t_list *lst);

char		*find_output(t_list *lst);

int			exec_redirect(t_list *lst);

char		*ft_strtok(char *str, const char *del);

int			count_list(t_list *lst);

int			total_input_len(t_list *lst);

int			here_doc(t_list *lst, char **env);

int			exec_pwd();

int			exec_echo(t_list *lst);

int			builtin_export(char *eval, t_data *data);

#endif
