/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:13:45 by laugarci          #+#    #+#             */
/*   Updated: 2023/07/14 12:38:15 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define READ_END 0
#define WRITE_END 1

int main(int ac, char **av)
{
	//un fd para cada pipe
	int fd1[2];
	int fd2[2];
	int status; //estado de los hijos
	int pid; //identificador de proceso

	pipe(fd1); //comunicara el primer comando con el segundo
	pid = fork(); //crea el primer hijo, hereda el fd del padre
	if (pid == 0) //hijo 1 que hereda el file descriptor del padre
	{
		close (fd1[READ_END]); //cerramos lo no necesario
		dup2(fd1[WRITE_END], STDOUT_FILENO); //guardamos lo que el primer comando escribe en el stdout en la pipe
		close(fd1[WRITE_END]);
		execlp("/bin/ls", "ls", "-l", NULL);
		/*
		 * CON EXECVE:
		 * char *const argv[] = { "ls", "-l", NULL }
		 * char *const envp[] = { NULL };
		 * execve("/bin/ls", argv, envp);
		 * return 0;
		 */
	}
	else //padre
	{
		close(fd1[WRITE_END]);

		pipe(fd2); //comunica grep y wc
		pid = fork();

		if (pid == 0) //hijo 2
		{
			close(fd2[READ_END]);
			dup2(fd1[READ_END], STDIN_FILENO); //dup para que lo que grep lea del pipe (del extremo de lectura) se lea del standard input del pipe
			close(fd1[READ_END]); //una vez duplicado no lo necesitO

			dup2(fd2[WRITE_END], STDOUT_FILENO); //lo que greo escribe en el standard output se escribe en el pipe
			close(fd2[WRITE_END]);

			execlp("/bin/grep", "grep", "u", NULL); //ejecutamos grep

		}
		else //padre
		{
			close(fd1[READ_END]);
			close(fd2[WRITE_END]);

			pid = fork();
			if (pid == 0) //hijo 3
			{
				dup2(fd2[READ_END], STDIN_FILENO);
				close(fd2[READ_END]);

				execlp("/usr/bin/wc", "wc", "-l", NULL);
			}
		}
	}
	close(fd2[READ_END]);
	wait(&status);
	wait(&status);
	wait(&status);

	return (0);
}
