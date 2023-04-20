# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/20 15:25:06 by mguerga           #+#    #+#              #
#    Updated: 2023/04/20 15:54:23 by mguerga          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Werror -Wall -Wextra

SRC_MINISH = mini_main.c ppx_checks.c ppx_free.c ppx_hd.c ppx_main.c \
			ppx_utils.c mini_gc.c

AR = ar rcs

RL = $(READLINE)

SOURCES = $(addprefix src/, $(SRC_MINISH))

OBJS = $(SOURCES:c=o)

all: $(NAME) 

$(NAME): $(OBJS) 
	make -C libft/
	$(CC) -Llibft/ -lft -I. -L$(RL)/lib -lreadline -I$(RL)/include $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS) 
	make clean -C libft/

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a 

re: fclean all

.PHONY: clean fclean re bonus 
