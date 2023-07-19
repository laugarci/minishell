/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_func_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:40:09 by laugarci          #+#    #+#             */
/*   Updated: 2023/07/19 13:10:39 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define READ_END 0
#define WRITE_END 1

int count_pipes(char *input)
{
    int count = 0;
    while (*input)
    {
        if (*input == '|')
            count++;
        input++;
    }
    return count + 1;
}

char *find_executable(char *command, char **env)
{
    char *path = getenv("PATH");
    if (path == NULL)
        return NULL;

    char *token = strtok(path, ":");
    while (token != NULL)
    {
        char *full_path = (char *)malloc(strlen(token) + strlen(command) + 2); // +2 for '/' and '\0'
        if (full_path == NULL)
            exit(1);
        sprintf(full_path, "%s/%s", token, command);
        if (access(full_path, X_OK) == 0)
            return full_path;
        free(full_path);
        token = strtok(NULL, ":");
    }

    return NULL;
}

void free_args(char **args)
{
    for (int i = 0; args[i] != NULL; i++)
    {
        free(args[i]);
        args[i] = NULL;
    }
}

void exec_pipes(char *input, char **env)
{
    int num_pipes;
    int fds[count_pipes(input)][2];
    int status;
    int i;
    pid_t pid;
    char *command;
    env = NULL; // Note: You might want to remove this line, as it is setting env to NULL.

    num_pipes = count_pipes(input);
    i = 0;
    while (i < num_pipes)
    {
        pipe(fds[i]);
        i++;
    }
    i = 0;
    command = strtok(input, "|");
    while (command != NULL)
    {
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
            if (i != num_pipes)
            {
                close(fds[i][READ_END]);
                dup2(fds[i][WRITE_END], STDOUT_FILENO);
                close(fds[i][WRITE_END]);
            }

            // Split the command into arguments
            char **args = (char **)malloc(64 * sizeof(char *));
            if (args == NULL)
                exit(1);

            int argIndex = 0;
            char *token = strtok(command, " ");
            while (token != NULL)
            {
                args[argIndex] = (char *)malloc(strlen(token) + 1);
                if (args[argIndex] == NULL)
                {
                    free_args(args);
                    exit(1);
                }
                strlcpy(args[argIndex], token, strlen(token) + 1);
                argIndex++;
                token = strtok(NULL, " ");
            }
            args[argIndex] = NULL;

            char *executable_path = find_executable(args[0], env);
            if (executable_path == NULL)
            {
                fprintf(stderr, "Command not found: %s\n", args[0]);
                free_args(args);
                exit(1);
            }

            execve(executable_path, args, env);
            perror("execve"); // If execve fails, print an error message.
            free_args(args);
            exit(1);
        }
        else
        {
            if (i != 0)
                close(fds[i - 1][READ_END]);
            if (i != num_pipes)
                close(fds[i][WRITE_END]);
        }
        command = strtok(NULL, "|");
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

int main() {
    char input[] = "ls -l | grep .txt";
    char *env[] = { NULL };
    exec_pipes(input, env);
    return 0;
}

