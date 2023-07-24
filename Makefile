# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/26 15:00:09 by ffornes-          #+#    #+#              #
#    Updated: 2023/07/24 17:18:38 by ffornes-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = src/
SRC_FILES = minishell.c get_path.c put_error.c parse_input.c here_doc.c exec_commands.c exec_pipes.c expansion.c quotes.c

OBJ_DIR = objs/
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

DEP_FILES = $(SRC_FILES:.c=.d)
DEPS = $(addprefix $(OBJ_DIR), $(DEP_FILES))

LIBFT = libft/libft.a

CC = 		gcc
CFLAGS = 	-Wall -Wextra -Werror -MMD
RM = 		rm -f
INCLUDE =	-I include/ -I libft/include/

all:		m_libft $(NAME)

m_libft:
			@make -C libft/

$(NAME):	$(OBJ_DIR) $(OBJS)
			$(CC) $(OBJS) -L libft/ -lft -o $@ -lreadline


$(OBJ_DIR):
			@mkdir $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(LIBFT) Makefile
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
			$(RM) $(OBJS) $(DEPS)
			@make -C libft/ clean

fclean:	clean
		$(RM) $(NAME)
		rmdir $(OBJ_DIR)
		@make -C libft/ fclean

re:	fclean all

-include $(DEPS)

.PHONY: all clean fclean re
