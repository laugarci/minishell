#include <stdio.h>
#include <readline/readline.h>
#include <readline/readline.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[]) 
{
	char *input;

	while (1)
	{
		input = readline("Ingrese una línea: ");
		printf("Ingresaste: %s\n", input);
		free(input);
	}
	return 0;
}
