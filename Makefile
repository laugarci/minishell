# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/26 15:00:09 by ffornes-          #+#    #+#              #
#    Updated: 2023/09/04 16:00:45 by laugarci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = src/
SRC_FILES = minishell.c \
			parse_input.c clean_input.c clean_input_utils.c split_input.c \
			expansion.c expansion_utils.c \
			get_path.c exec_commands.c exec_pipes.c exec_here_doc.c \
			put_error.c exec_redirec.c utils.c find_command.c exec_pwd.c exec_echo.c \
			quotes.c \
			token_new.c token_free.c token_save.c \
			token_process.c token_process_rm.c token_process_subtoken.c \
			builtin_export.c \

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
		rmdir $(OBJ_DIR)
		$(RM) $(NAME)
		$(RM) -rf $(OBJ_DIR)
		@make -C libft/ fclean

re:	fclean all

-include $(DEPS)

.PHONY: all clean fclean re
