/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 13:56:23 by laugarci          #+#    #+#             */
/*   Updated: 2023/06/30 14:01:18 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <comando>\n", argv[0]);
        return 1;
    }

    char *comando = argv[1];

    pid_t pid = fork();
    if (pid == -1) {
        perror("Error en fork");
        return 1;
    } else if (pid == 0) {
        int command_length = strlen(comando);
        char *command = malloc(command_length + 1);
        if (command == NULL) {
            perror("Error en malloc");
            exit(1);
        }
        strncpy(command, comando, command_length);
        command[command_length] = '\0';

        char **args = malloc((argc - 1 + 1) * sizeof(char *));
        if (args == NULL) {
            perror("Error en malloc");
            exit(1);
        }
        int i;
        for (i = 1; i < argc; i++) {
            int arg_length = strlen(argv[i]);
            args[i - 1] = malloc(arg_length + 1);
            if (args[i - 1] == NULL) {
                perror("Error en malloc");
                exit(1);
            }
            strncpy(args[i - 1], argv[i], arg_length);
            args[i - 1][arg_length] = '\0';
        }
        args[i - 1] = NULL;
        exit(1);
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("Comando ejecutado\n");
        }
    }

    return 0;
}

