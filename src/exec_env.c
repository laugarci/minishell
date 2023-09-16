

#include <stdio.h>
#include "minishell.h"

int	exec_env(char **env)
{
	int i;
	
	i = 0;
	while (env[i] != NULL)
		printf("%s\n", env[i++]);
	return (0);
}
