# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/20 20:55:12 by mguerga           #+#    #+#              #
#    Updated: 2023/04/23 11:00:19 by mguerga          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Werror -Wall -Wextra

SRC_MINISH = mini_main.c ppx_checks.c ppx_free.c ppx_hd.c ppx_main.c \
			ppx_utils.c mini_gc.c mini_sig.c mini_utils.c

AR = ar rcs

RL = $(READLINE)

SOURCES = $(addprefix src/, $(SRC_MINISH))

OBJS = $(SOURCES:c=o)

all: $(NAME) 

$(NAME): $(OBJS) 
	make -C libft/
	$(CC) $(CFLAGS) $(OBJS) -I. -L$(RL)/lib -lreadline -I$(RL)/include -Llibft/ -lft -o $(NAME)

clean:
	rm -f $(OBJS) 
	make clean -C libft/

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a 

re: fclean all

.PHONY: clean fclean re bonus 
