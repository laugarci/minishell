/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:50:31 by laugarci          #+#    #+#             */
/*   Updated: 2023/08/16 17:06:43 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	exec_pipes(t_list *lst, char **env, int num_pipes)
{
	int		status;
	int		i;
	pid_t	pid;
	char	*command;
	int		**fds;
	t_list	*aux;
	char	*input;

	i = 0;
	fds = malloc(sizeof(int *) * num_pipes);
	while (i < num_pipes)
	{
		fds[i] = malloc(sizeof(int) * 2);
		pipe(fds[i]);
		i++;
	}
	i = 0;
	input = find_command(lst);
	command = ft_strtok(input, "|");
	while (command != NULL)
	{
		char *output_redirect = strchr(command, '>');
		char *append_redirect = strchr(command, '>');

		pid = fork();
		if (pid == -1)
			exit(-1);
		else if (pid == 0)
		{
			if (i != 0)
			{
				close(fds[i - 1][WRITE_END]);
				dup2(fds[i - 1][READ_END], STDIN_FILENO);
				close(fds[i - 1][READ_END]);
			}
			if (output_redirect)
			{
				*output_redirect = '\0';
				int fd = open(output_redirect + 1, O_WRONLY | O_CREAT | O_TRUNC, 0666);
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
			if (append_redirect)
			{
				*append_redirect = '\0';
				int fd = open(append_redirect + 1, O_WRONLY | O_CREAT | O_APPEND, 0666);
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
			if (i != num_pipes)
			{
				close(fds[i][READ_END]);
				dup2(fds[i][WRITE_END], STDOUT_FILENO);
				close(fds[i][WRITE_END]);
			}
			aux = save_tokens(command);
			exec_commands(aux, env);
			exit(1);
		}
		else
		{
			if (i != 0)
				close(fds[i - 1][READ_END]);
			if (i != num_pipes)
				close(fds[i][WRITE_END]);
		}
		command = ft_strtok(NULL, "|");
		i++;
	}
	i = 0;
	while (i < num_pipes)
	{
		close(fds[i][READ_END]);
		close(fds[i][WRITE_END]);
		i++;
	}
	i = 0;
	while (i <= num_pipes)
	{
		wait(&status);
		i++;
	}
}


