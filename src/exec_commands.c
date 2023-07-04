#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void ft_exec_commands(char* input) {
    size_t command_len;
    size_t flags_len;
    char *space_pos;
    char *command;
    char *flags;
    char **args;
    int status;
    pid_t pid = fork();

    if (pid == 0)
    {
	    space_pos = ft_strchr(input, ' ');
	    if (space_pos != NULL)
	    {
		    command_len = space_pos - input;
		    flags_len = ft_strlen(space_pos + 1);
		    command = (char*)malloc((command_len + 1) * sizeof(char));
		    flags = (char*)malloc((flags_len + 1) * sizeof(char));
		    ft_strncpy(command, input, command_len);
		    ft_strncpy(flags, space_pos + 1, flags_len);
		    command[command_len] = '\0';
		    flags[flags_len] = '\0';
		    args = (char**)malloc(3 * sizeof(char*));
		    args[0] = command;
		    args[1] = flags;
		    args[2] = NULL;
		    execvp(command, args);
		    free(command);
		    free(flags);
		    free(args);
        }
        else
	{
            args = (char**)malloc(2 * sizeof(char*));
            args[0] = input;
            args[1] = NULL;
            execvp(input, args);
            free(args);
        }
    }
    else if (pid > 0)
        waitpid(pid, &status, 0);
}

