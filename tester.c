# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
/*   tester.c                                           :+:      :+:    :+:   */
#                                                     +:+ +:+         +:+      #
#    By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/18 17:09:36 by laugarci          #+#    #+#              #
/*   Updated: 2023/09/20 17:46:05 by laugarci         ###   ########.fr       */
#                                                                              #
# **************************************************************************** #

echo -nnnnn -nnnn loquesea
ls > a | ls > b
cat | ls
<a>b<c>d ls | wc -l < d | cat -e > e
ls > a
ls >> a
cat <<del
cat <<del > a
ls > a > b > c > d
ls >> a >> b >> c >> d
cd -
cd
cd ruta
ls -a | wc -l | cat -e
ls -a | cat << hola | cat -e
ls | cat
cat | ls
wc -l < Makefile > a
ls | wc < Makefile > a | cat<<hola > c | ls > b
 <<bla | cat << c
 > b< tester.c cat < Makefile <<bla > k | wc -l
----
cd -
cd carpeta/ anadir /



HERE_DOC:

#### NO FUNCIONA ####

<<del1 <<del2

ls<<a > b | bla<<b (ejecuta bla antes que nada)
ls<<bla > a | cat<<ble > b (guarda ls, no guarda cat, pero si es otro comando si guarda cosas)
ls<<a > b | ls<<b (ejecuta el segundo comando antes que nada)
cat<<a | <<a (imprime el cat)
cat<<a > b | <<b (guarda lo escrito cuando esta en el 2do delimitador)
cat<<bla > a | ls<<ble > b (guarda bien el ls, pero guarda en a lo que se escribe cuando estas en el 2do delimitador)
>>problemas genericos con CAT y el texto

##### FUNCIONA #####

cat<<a
ls<<a > b | <<b
cmd<<del | cmd<<del
ls<<a > b | <<b
<<del
cmd<<del
cmd<<del | cmd<<del
cmd<<del > b | cmd<<del > a (ls<<del > b | wc<<del2 > a)
ls | wc < Makefile > a | cat<<hola > c | ls > b

