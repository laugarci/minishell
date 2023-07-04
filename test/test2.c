/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:14:59 by laugarci          #+#    #+#             */
/*   Updated: 2023/06/30 14:30:59 by laugarci         ###   ########.fr       */
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

void ejecutar_comando(char *comando, char *args[]) {
    pid_t pid = fork();
 //   if (pid == -1) {
   //     perror("Error en fork");
     //   exit(1);
//    } else if (pid == 0) {
        execvp(comando, args);

/*        char error_message[256];
        snprintf(error_message, sizeof(error_message), "Error en execvp: %s", strerror(errno));
        perror(error_message);
        exit(1);
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("Comando ejecutado\n");
        }
    }*/
}

int main(int argc, char *argv[]) {

    char *comando = argv[1];
    char **args = malloc((argc - 1 + 1) * sizeof(char *));
    if (args == NULL) {
        perror("Error en malloc");
        return 1;
    }

    int i;
    for (i = 1; i < argc; i++) {
        args[i - 1] = argv[i];
    }
    args[i - 1] = NULL;

    ejecutar_comando(comando, args);

    free(args);

    return 0;
}

