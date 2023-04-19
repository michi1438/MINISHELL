/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:03:15 by lzito             #+#    #+#             */
/*   Updated: 2022/12/03 20:21:38 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../srcs/libft.h"
# include <stdint.h>

int	ft_printf(const char *format, ...);
int	ft_putchar(char c);
int	ft_putstr(char *s);
int	ft_putnbr(long int n);
int	ft_putnbr_u(unsigned int n);
int	ft_putnbr_16(unsigned int n, char sign);
int	ft_put_p(uintptr_t n);
int	ft_nblen(int n);

#endif
