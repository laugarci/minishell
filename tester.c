# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
/*   tester.c                                           :+:      :+:    :+:   */
#                                                     +:+ +:+         +:+      #
#    By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/18 17:09:36 by laugarci          #+#    #+#              #
/*   Updated: 2023/09/21 16:56:13 by laugarci         ###   ########.fr       */
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
ls<<a > b | bla<<b
REDIRECCIONES EN EL PRIMER COMANDO


#### FUNCIONA #####
<<del1 <<del2
ls << a | ls << b
ls << a | ls << b > a
ls | wc < Makefile > a | cat<<hola > c | ls > b
cat<<a | <<b
cat<<a | cat<<b > b
ls<<a | cat<<b > z
cmd-no-existe << del | ls<<del
<<del
cat<<a
ls<<a | ls<<b > c | ls
