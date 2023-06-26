# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/24 19:51:17 by ffornes-          #+#    #+#              #
#    Updated: 2023/05/18 10:52:20 by ffornes-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INCLUDES = include/

###############################################################################
#									SRCS									  #
###############################################################################

SRCS_LIBFT_DIR = srcs/
SRC_FILES =	 ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			 ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
			 ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
			 ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
			 ft_atoi.c ft_calloc.c ft_strdup.c ft_strdup.c ft_substr.c \
			 ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
			 ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
			 ft_putnbr_fd.c \
			 ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			 ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
			 ft_lstmap.c \
			 ft_delete.c ft_lstpos.c ft_atoi_base.c
SRCS_LIBFT = $(addprefix $(SRCS_LIBFT_DIR), $(SRC_FILES))

SRCS_PRINTF_DIR = ft_printf/srcs/
SRC_PRINTF_FILES = print_c.c print_d.c print_p.c print_s.c print_u.c print_x.c \
				   ft_printf.c
SRCS_PRINTF = $(addprefix $(SRCS_PRINTF_DIR), $(SRC_PRINTF_FILES))

SRCS_GNL_DIR = get_next_line/
SRC_GNL_FILES =	get_next_line.c
SRCS_GNL = $(addprefix $(SRCS_GNL_DIR), $(SRC_GNL_FILES))

###############################################################################
#									OBJS									  #
###############################################################################

OBJS_LIBFT_DIR =	objs/
OBJ_LIBFT_FILES =	$(SRC_FILES:.c=.o)
OBJS_LIBFT = $(addprefix $(OBJS_LIBFT_DIR), $(OBJ_LIBFT_FILES))

OBJS_PRINTF_DIR =	ft_printf/objs/
OBJ_PRINTF_FILES =	$(SRC_PRINTF_FILES:.c=.o)
OBJS_PRINTF = $(addprefix $(OBJS_PRINTF_DIR), $(OBJ_PRINTF_FILES))

OBJS_GNL_DIR =	get_next_line/objs/
OBJ_GNL_FILES = $(SRC_GNL_FILES:.c=.o)
OBJS_GNL = $(addprefix $(OBJS_GNL_DIR), $(OBJ_GNL_FILES))

OBJS = $(OBJS_LIBFT) $(OBJS_PRINTF) $(OBJS_GNL)

###############################################################################
#									OTHER									  #
###############################################################################

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
AR = ar rc

HDR_DIR = include/
HDR_FILES = libft.h ft_printf.h get_next_line.h
HDRS = $(addprefix $(HDR_DIR), $(HDR_FILES))

###############################################################################
#									RULES									  #
###############################################################################

all: 		$(NAME) $(HDRS)

$(NAME):	$(OBJS_LIBFT_DIR) $(OBJS_PRINTF_DIR) $(OBJS_GNL_DIR) $(OBJS)
			$(AR) $@ $(OBJS)

$(OBJS_LIBFT_DIR):		
						@mkdir $(OBJS_LIBFT_DIR)

$(OBJS_PRINTF_DIR):
						@mkdir $(OBJS_PRINTF_DIR)

$(OBJS_GNL_DIR):
						@mkdir $(OBJS_GNL_DIR)

$(OBJS_LIBFT_DIR)%.o:	$(SRCS_LIBFT_DIR)%.c include/libft.h
						$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

$(OBJS_PRINTF_DIR)%.o:	$(SRCS_PRINTF_DIR)%.c include/ft_printf.h
						$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

$(OBJS_GNL_DIR)%.o:		$(SRCS_GNL_DIR)%.c include/get_next_line.h
						$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

clean: 		
			@$(RM) $(OBJS)

fclean: 	clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re
