# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
/*   tester.c                                           :+:      :+:    :+:   */
#                                                     +:+ +:+         +:+      #
#    By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/18 17:09:36 by laugarci          #+#    #+#              #
/*   Updated: 2023/09/24 12:51:46 by laugarci         ###   ########.fr       */
#                                                                              #
# **************************************************************************** #

NO FUNCIONA:
cat | ls
cd ../../
cd ~/Users
cd ~

FUNCIONA:
echo -nnnnn -nnnn loquesea
ls > a | ls > b
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
wc -l < Makefile > a
ls | wc < Makefile > a | cat<<hola > c | ls > b
 <<bla | cat << c
 > b< tester.c cat < Makefile <<bla > k | wc -l
----
cd -
cd carpeta/ anadir /
ls | wc < Makefile > a | cat<<hola > c | ls > b (no redireciona cat, pero si ls)
cat<<a | <<b
<<a | cat<<b
ls<<a | cat<<b > b (redirecciona ls)
cat en general no funciona
cat<<a
ls<<a > b | bla<<b
<<del <<del
ls<<a | ls<<b
ls<<a | ls<<b > a
cmd-no-existe << del | ls<<del
<<del
ls<<a | ls<<b > c | ls
