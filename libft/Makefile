# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/26 13:44:34 by dbrandtn          #+#    #+#              #
#    Updated: 2022/05/19 17:08:17 by dbrandtn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a
SRCS := ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
	ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
	ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
	ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
	ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_utoa.c \
	ft_put_uint_fd.c ft_printf.c ft_printf_mod.c ft_printf_mod_hex.c \
	get_next_line.c get_next_line_utils.c ft_atoi_hex.c ft_iswhitespace.c \
	ft_isnum.c ft_str_trim_end.c ft_strcmp.c
SRCS_LIST := list.c list_cleanup.c list_add_rm.c list_get.c list_utils.c
SRCS_VECTOR := vector.c vector_add_rm.c
SRCS_STACK := stack.c
OBJS := $(SRCS:.c=.o)
OBJS_LIST := $(SRCS_LIST:.c=.o)
OBJS_VECTOR := $(SRCS_VECTOR:.c=.o)
OBJS_STACK := $(SRCS_STACK:.c=.o)
CC ?= cc
LD ?= cc
CFLAGS = -Wall -Wextra -Werror

$(NAME): $(OBJS)
	ar r $(NAME) $^

.PHONY: all list vector stack debug clean fclean re

all: $(NAME) list vector stack

list: $(NAME) $(OBJS_LIST)
	ar r $^

vector: $(NAME) $(OBJS_VECTOR)
	ar r $^

stack: $(NAME) $(OBJS_STACK)
	ar r $^

debug: CFLAGS += -g3
debug: re
# -D FT_DEBUG_MEMORY

clean:
	rm -f $(OBJS) $(OBJS_LIST) $(OBJS_VECTOR) $(OBJS_STACK)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@
