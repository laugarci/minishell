# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/26 15:00:09 by ffornes-          #+#    #+#              #
#    Updated: 2023/09/22 14:51:11 by laugarci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = src/
SRC_FILES = minishell.c \
			init_env.c env_var_free.c env_var_new.c env_var_to_charpp.c \
			parse_input.c clean_input.c clean_input_utils.c split_input.c \
			expansion.c expansion_utils.c expansion_update.c \
			get_path.c exec_commands.c exec_pipes.c exec_here_doc.c \
			exec_redirec.c utils.c find_command.c exec_pwd.c exec_echo.c \
			quotes.c \
			token_new.c token_free.c token_save.c token_type.c \
			token_process.c token_process_rm.c \
			subtoken_process.c subtoken_count.c subtoken_join.c token_organize.c \
			builtin_export.c builtin_exit.c \
			errors.c syntax_error.c process_list.c exec_cd.c exec_env.c exec_unset.c check.c \
			signals.c exit_status.c

OBJ_DIR = objs/
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

DEP_FILES = $(SRC_FILES:.c=.d)
DEPS = $(addprefix $(OBJ_DIR), $(DEP_FILES))

LIBFT = libft/libft.a

CC = 		gcc
CFLAGS = 	-Wall -Wextra -Werror -MMD #-fsanitize=address
RM = 		rm -f
INCLUDE =	-I include/ -I libft/include/ -I ~/.brew/Cellar/readline/8.2.1/include/

all:		m_libft $(NAME)

m_libft:
			@make -C libft/

$(NAME):	$(OBJ_DIR) $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -L libft/ -lft -o $@ -L ~/.brew/Cellar/readline/8.2.1/lib/ -lreadline -lhistory -ltermcap


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
