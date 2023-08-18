/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:16:54 by laugarci          #+#    #+#             */
/*   Updated: 2023/08/18 12:17:00 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_ARGS 10
#define MAX_COMMAND_LENGTH 1024

void handle_redirections(char *command, char *input_file, char *output_file);

int main() {
    char *command;
    char *args[MAX_ARGS];
    char *input_file = NULL;
    char *output_file = NULL;

    while (1) {
        command = readline("MiShell> ");
        if (!command)
            break;

        if (strcmp(command, "exit") == 0) {
            free(command);
            break;
        }

        // Tokenize command
        int num_args = 0;
        args[num_args] = strtok(command, " ");
        while (args[num_args] != NULL && num_args < MAX_ARGS - 1) {
            num_args++;
            args[num_args] = strtok(NULL, " ");
        }
        args[num_args] = NULL;

        if (num_args > 0) {
            // Check for input/output redirection
            for (int i = 0; i < num_args; i++) {
                if (strcmp(args[i], "<") == 0) {
                    input_file = args[i + 1];
                    args[i] = NULL;
                    i++; // Skip the next argument (input file)
                } else if (strcmp(args[i], ">") == 0) {
                    output_file = args[i + 1];
                    args[i] = NULL;
                    i++; // Skip the next argument (output file)
                }
            }

            handle_redirections(args[0], input_file, output_file);

            input_file = NULL;
            output_file = NULL;
        }

        add_history(command);
        free(command);
    }

    return 0;
}

void handle_redirections(char *command, char *input_file, char *output_file) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("Fork failed");
        return;
    }

    if (pid == 0) {
        // Child process

        // Handle input redirection
        if (input_file) {
            int fd = open(input_file, O_RDONLY);
            if (fd == -1) {
                perror("Error opening input file");
                exit(1);
            }
            if (dup2(fd, STDIN_FILENO) == -1) {
                perror("Dup2 failed for input redirection");
                close(fd);
                exit(1);
            }
            close(fd);
        }

        // Handle output redirection
        if (output_file) {
            int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1) {
                perror("Error opening output file");
                exit(1);
            }
            if (dup2(fd, STDOUT_FILENO) == -1) {
                perror("Dup2 failed for output redirection");
                close(fd);
                exit(1);
            }
            close(fd);
        }

        // Execute the command
        if (execvp(command, args) == -1) {
            perror("Execvp failed");
            exit(1);
        }
    } else {
        // Parent process
        waitpid(pid, NULL, 0);
    }
}

