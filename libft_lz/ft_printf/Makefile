# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lzito <marvin@42lausanne.ch>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/12 13:26:00 by lzito             #+#    #+#              #
#    Updated: 2022/12/03 17:58:07 by lzito            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a

SRCS	= ft_printf.c\
		  ft_nblen.c\
		  ft_put_p.c\
		  ft_putchar.c\
		  ft_putnbr.c\
		  ft_putnbr_16.c\
		  ft_putnbr_u.c\
		  ft_putstr.c

OBJS	= ${SRCS:.c=.o}

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

RM		= rm -f

CC		= gcc

AR		= ar rcs

CFLAGS	= -Wall -Wextra -Werror

${NAME}:	${OBJS}
			${AR} ${NAME} ${OBJS}

all:	${NAME}

clean:	
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re
