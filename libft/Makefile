# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 15:04:36 by malaakso          #+#    #+#              #
#    Updated: 2023/07/15 17:12:26 by malaakso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLGS = -Wall -Wextra -Werror -Wpedantic -Wunreachable-code -Wtype-limits
COMPILE = $(CC) $(CFLGS) -c
AR = ar rucs $(NAME) $(OBJS)

SRCS	=	basic/ft_isalpha.c \
			basic/ft_isdigit.c \
			basic/ft_isalnum.c \
			basic/ft_isascii.c \
			basic/ft_isprint.c \
			basic/ft_strlen.c \
			basic/ft_memset.c \
			basic/ft_bzero.c \
			basic/ft_memcpy.c \
			basic/ft_memmove.c \
			basic/ft_strlcpy.c \
			basic/ft_strlcat.c \
			basic/ft_toupper.c \
			basic/ft_tolower.c \
			basic/ft_strchr.c \
			basic/ft_strrchr.c \
			basic/ft_strncmp.c \
			basic/ft_memchr.c \
			basic/ft_memcmp.c \
			basic/ft_strnstr.c \
			basic/ft_atoi.c \
			basic/ft_calloc.c \
			basic/ft_strdup.c \
			basic/ft_substr.c \
			basic/ft_strjoin.c \
			basic/ft_strtrim.c \
			basic/ft_split.c \
			basic/ft_itoa.c \
			basic/ft_strmapi.c \
			basic/ft_striteri.c \
			basic/ft_putchar_fd.c \
			basic/ft_putstr_fd.c \
			basic/ft_putendl_fd.c \
			basic/ft_putnbr_fd.c \
			basic/ft_strrev.c \
			basic/ft_strndup.c \
			printf/ft_printf.c \
			printf/ft_printf_utils.c \
			printf/ft_printf_spec_hex.c \
			gnl/get_next_line.c \
			vec/vec_copy.c \
			vec/vec_free.c \
			vec/vec_from.c \
			vec/vec_get.c \
			vec/vec_insert.c \
			vec/vec_new.c \
			vec/vec_pop.c \
			vec/vec_push.c \
			vec/vec_remove.c \
			vec/vec_resize.c

OBJS = $(SRCS:%.c=%.o)

.PHONY: Makefile

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(AR)

%.o: %.c
	$(COMPILE) $< -o $@

.PHONY: clean
clean:
	/bin/rm -f $(OBJS)

.PHONY: fclean
fclean: clean
	/bin/rm -f $(NAME)

.PHONY: re
re: fclean all
