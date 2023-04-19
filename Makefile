# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/19 15:35:52 by mguerga           #+#    #+#              #
#    Updated: 2023/04/19 20:34:10 by lzito            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Werror -Wall -Wextra

SRC_MINISH = mini_main.c ppx_checks.c ppx_free.c ppx_hd.c ppx_main.c \
			ppx_utils.c

AR = ar rcs

SOURCES = $(addprefix src/, $(SRC_MINISH))

OBJS = $(SOURCES:c=o)

all: $(NAME) 

$(NAME): $(OBJS) 
	make -C libft/
	$(CC) -lft -L./libft $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS) 
	make clean -C libft/

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a 

re: fclean all

.PHONY: clean fclean re bonus 
