/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:04:50 by laugarci          #+#    #+#             */
/*   Updated: 2023/07/06 15:05:22 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    int fd[3][2];
    int i;
    for (i = 0; i < 3; i++) {
        if (pipe(fd[i]) < 0) {
            return 1;
        }
    }
    
    int pid1 = fork();
    if (pid1 < 0) {
        return 2;
    }
    
    if (pid1 == 0) {
        // Child process 1
        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[2][0]);
        close(fd[2][1]);
        int x = 0;
        if (read(fd[0][0], &x, sizeof(int)) < 0) {
            return 3;
        }
        x += 5;
        if (write(fd[1][1], &x, sizeof(int)) < 0) {
            return 4;
        }
        close(fd[0][0]);
        close(fd[1][1]);
        return 0;
    }
    
    int pid2 = fork();
    if (pid2 < 0) {
        return 5;
    }
    
    if (pid2 == 0) {
        // Child process 2
        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[1][1]);
        close(fd[2][0]);
        int x = 0;
        if (read(fd[1][0], &x, sizeof(int)) < 0) {
            return 6;
        }
        x += 5;
        if (write(fd[2][1], &x, sizeof(int)) < 0) {
            return 7;
        }
        close(fd[1][0]);
        close(fd[2][1]);
        return 0;
    }
    
    // Parent process
    close(fd[0][0]);
    close(fd[1][0]);
    close(fd[1][1]);
    close(fd[2][1]);
    int x = 0;
    if (write(fd[0][1], &x, sizeof(int)) < 0) {
        return 8;
    }
    if (read(fd[2][0], &x, sizeof(int)) < 0) {
        return 9;
    }
    printf("Result is %d\n", x);
    close(fd[0][1]);
    close(fd[2][0]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
