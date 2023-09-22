/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 11:32:21 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/22 14:50:45 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "libft_defs.h"
# include "minishell_defs.h"

t_list		*set_env(char *envp[]);

void		free_var(t_env *var);
t_env		*new_env_var(char *str);
t_env		*char_to_tenv(char *input);
char		**envlst_to_charpp(t_list *lst);

char		*get_path(char *cmd, char **envp);

int			exec_commands(t_list *lst, char **env);
int			exec_commands_wf(t_list *lst, char **env, int flags);
int			exec_commands_other(char *space_pos, char *input, char **env);
int	        cmp_commands(t_list *lst, t_list **env_lst, char **env);

int			exec_cd(t_list *lst);

int			is_type(t_list *lst, int type);
int			count_types(t_list *lst, int type);

int			exec_pipes(char **env, int num_pipes, t_list *lst);

int			count_args(t_list *lst);

int			**close_pipes(int **fds, int num_pipes);

char		*find_command(t_list *lst);

char		*find_output(t_list *lst, int check);

int			exec_redirect(t_list *lst);

int			count_list(t_list *lst);
int			total_input_len(t_list *lst);
int			*here_doc(t_list *lst);
int			exec_pwd(void);
int			exec_echo(t_list *lst);

void		print_error(char *error_message);
int			print_and_return(int error_id);

t_list		*process_list(t_list *lst, int i);
int			check_redirect(t_list *lst);
t_list		*move_to_pipe(t_list *lst);
int			check_infile(t_list *lst);
int			exec_env(char **env);
int			exec_unset(t_list *lst, char **env);
int			*signal_handler(void);

int			set_or_return_exit_status(int mode, int value);
int			set_or_return_state(int mode, int value);

void		signal_display(int mode);

int			check_error(int error);

void		builtin_exit(char *input);
void		exit_check(t_list *lst);

int			process_is_type(t_list *lst, int type);
int			builtin_export(t_list *tkn_lst, t_list **env_lst);

char		*find_input(t_list *lst);

#endif
