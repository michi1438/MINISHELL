# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/20 20:55:12 by mguerga           #+#    #+#              #
#    Updated: 2023/06/07 17:11:37 by mguerga          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Werror -Wall -Wextra -I$(RL)/include -I. -g3 #-fsanitize=leak \
		 -fsanitize=address -fsanitize=undefined

SRC_MINISH = mini_main.c ppx_checks.c ppx_free.c ppx_main.c ppx_utils.c\
			mini_gc.c mini_sig_n_attr.c mini_utils.c mini_tokenable.c \
			mini_not_tokenable.c mini_errors.c mini_expand.c For_testing_only.c \
			mini_append_or_start.c mini_builtins.c mini_mod_split.c mini_redir.c \
			mini_prefork_builtin.c mini_prefork_unset.c mini_prefork_export.c \
			mini_redir_cmds.c mini_builtins_echo.c mini_expand_size.c \
		   	mini_init.c mini_wraps.c mini_sa_handlers.c mini_utils_env.c \
			mini_utils_lst.c ppx_init.c mini_init_add_cmds.c

AR = ar rcs

RL = $(READLINE)

SOURCES = $(addprefix src/, $(SRC_MINISH))

OBJS = $(SOURCES:c=o)

all: $(NAME) 

$(NAME): $(OBJS) 
	make -C libft/
	$(CC) $(CFLAGS) $(OBJS) -L$(RL)/lib -lreadline -lhistory -Llibft/ -lft -o $(NAME)

clean:
	rm -f $(OBJS) 
	make clean -C libft/

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a 

re: fclean all

.PHONY: clean fclean re bonus 
