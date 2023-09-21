# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
/*   tester.c                                           :+:      :+:    :+:   */
#                                                     +:+ +:+         +:+      #
#    By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/18 17:09:36 by laugarci          #+#    #+#              #
/*   Updated: 2023/09/21 19:25:17 by laugarci         ###   ########.fr       */
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
ls | wc < Makefile > a | cat<<hola > c | ls > b (no redireciona cat, pero si ls)
cat<<a | <<b
<<a | cat<<b
ls<<a | cat<<b > b (redirecciona ls)
cat en general no funciona

### FUNCIONA ###
cat<<a
ls<<a > b | bla<<b
<<del <<del
ls<<a | ls<<b
ls<<a | ls<<b > a
cmd-no-existe << del | ls<<del
<<del
ls<<a | ls<<b > c | ls
