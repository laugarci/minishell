#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void execute_with_pipes(char **args1, char **args2, char **env) {
    int pipefd[2]; // Array para almacenar los descriptores de archivo del pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return;
    }

    pid_t pid1, pid2;

    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
        return;
    }

    if (pid1 == 0) { // Proceso hijo 1 (ejecuta el primer comando)
        // Redirigir la salida estándar al extremo de escritura del pipe
        close(pipefd[0]); // No se necesita el extremo de lectura del pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execve(args1[0], args1, env);
        perror("execve");
        exit(1);
    }

    // Proceso padre
    pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
        return;
    }

    if (pid2 == 0) { // Proceso hijo 2 (ejecuta el segundo comando)
        // Redirigir la entrada estándar al extremo de lectura del pipe
        close(pipefd[1]); // No se necesita el extremo de escritura del pipe
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        execve(args2[0], args2, env);
        perror("execve");
        exit(1);
    }

    // Proceso padre
    close(pipefd[0]);
    close(pipefd[1]);

    // Esperar a que ambos hijos terminen su ejecución
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

void parse_and_execute(char *input, char **env) {
    // Dividir la cadena de entrada en dos comandos separados por '|'
    char *command1 = strtok(input, "|");
    char *command2 = strtok(NULL, "|");

    // Eliminar espacios en blanco al inicio y final de los comandos
    trim_whitespace(command1);
    trim_whitespace(command2);

    // Crear arreglos para almacenar los argumentos de cada comando
    char **args1 = split_arguments(command1);
    char **args2 = split_arguments(command2);

    // Ejecutar los comandos con pipes
    execute_with_pipes(args1, args2, env);

    // Liberar la memoria de los arreglos de argumentos
    free_arguments(args1);
    free_arguments(args2);
}

void trim_whitespace(char *str) {
    // Eliminar espacios en blanco al inicio de la cadena
    while (*str == ' ' || *str == '\t') {
        str++;
    }

    // Eliminar espacios en blanco al final de la cadena
    size_t len = strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t')) {
        str[len - 1] = '\0';
        len--;
    }
}

char **split_arguments(char *command) {
    const char *delimiters = " \t"; // Espacios y tabulaciones como delimitadores
    const int max_arguments = 64; // Número máximo de argumentos permitidos
    char **args = malloc(sizeof(char *) * (max_arguments + 1)); // +1 para el último elemento NULL
    int arg_count = 0;

    // Dividir la cadena en argumentos utilizando strtok
    char *token = strtok(command, delimiters);
    while (token != NULL) {
        args[arg_count] = strdup(token); // Copiar cada argumento en un nuevo espacio de memoria
        arg_count++;

        // Verificar si se alcanzó el número máximo de argumentos permitidos
        if (arg_count >= max_arguments) {
            break;
        }

        token = strtok(NULL, delimiters);
    }

    args[arg_count] = NULL; // Establecer el último elemento del arreglo como NULL

    return args;
}

void free_arguments(char **args) {
    for (int i = 0; args[i] != NULL; i++) {
        free(args[i]);
    }
    free(args);
}

int main(int argc, char *argv[], char *envp[]) {
    char *input;
    char *prompt;
    char **env;

    if (argc > 1)
        exit(1);
    env = set_env(envp);
    if (!env) // mem error
        return (1);
    prompt = ft_strjoin(argv[0], " > ");
    if (!prompt)
        return (1);
    while (1) {
        input = readline(prompt);
        if (input[0] != '\0' && input) {
            add_history(input);
            exit_check(input);
            parse_input(input, envp);
            parse_and_execute(input, env);
        }
        free(input);
    }
    return (0);
}

