/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:50:49 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/04 15:15:36 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



void my_echo(int argc, char *argv[]) {

    for (int i = 1; i < argc; i++) {
        char *arg = argv[i];
        if (arg[0] == '$') {
            // Si el argumento comienza con '$', intenta obtener el valor de la variable de entorno.
            char *env_var_name = arg + 1; // Omite el '$'
		  	 char *env_var_value = getenv(env_var_name);
            if (env_var_value != NULL) {
                printf("%s", env_var_value);
            } else {
                printf("%s", arg); // Si no se encuentra la variable de entorno, imprime el nombre tal cual.
            }
        } else {
            printf("%s", arg);
        }

        if (i < argc - 1) {
            printf(" ");
        }
    }
    printf("\n");
}
