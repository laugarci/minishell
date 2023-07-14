/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 11:32:21 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/14 10:09:04 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

int		parse_input(char *str, char *envp[]);

char	*get_path(char **cmd, char **envp);

char	*here_doc(char **input, char *envp[]);

void	put_error(char *str, int error_id);

int		exec_commands(char *input, char **env);

int		cmp_commands(char *input, char **env);

int		exec_cd(char **input);

//testing
int		is_pipe(char *entrada);

size_t	mi_strspn(const char *str, const char *delimiters);

char	*ft_strpbrk(const char *str, const char *delimiters);

char	*ft_strtok(char *str, const char *delimiters, char **resto);

void	ejecutar_comandos(char *entrada);

#endif
