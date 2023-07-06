/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_chdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:09:39 by laugarci          #+#    #+#             */
/*   Updated: 2023/07/06 15:19:55 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int main() {
    char path[256];

    printf("Directorio actual: %s\n", getcwd(path, sizeof(path)));

    if (chdir("./hola") == 0) {
        printf("Directorio cambiado exitosamente.\n");
    } else {
        printf("No se pudo cambiar de directorio.\n");
    }

    printf("Nuevo directorio actual: %s\n", getcwd(path, sizeof(path)));

    return 0;
}

