/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 11:32:21 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/25 16:21:23 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

int			parse_input(char **str, char *envp[]);

char		*get_path(char **cmd, char **envp);

char		*here_doc(char **input, char *envp[]);

void		put_error(char *str, int error_id);

int			exec_commands(char *input, char **env);

int			cmp_commands(char *input, char **env);

int			exec_cd(char **input);

int			is_pipe(char *entrada);

int			count_chars(char *input, char del);

void		exec_pipes(char *input, char **env, int num_pipes);

void		exec_command_pipes(char *command, char **env);

char		*expand_evals(char *input, char *envp[]);
int			expansion_amount(char *input);
char		*find_eval(char *str, char *envp[]);

char		*remove_quotes(char *str);

#endif
