# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
/*   tester.c                                           :+:      :+:    :+:   */
#                                                     +:+ +:+         +:+      #
#    By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/18 17:09:36 by laugarci          #+#    #+#              #
/*   Updated: 2023/09/19 18:08:27 by laugarci         ###   ########.fr       */
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

