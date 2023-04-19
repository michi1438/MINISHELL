/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_16.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 23:44:59 by lzito             #+#    #+#             */
/*   Updated: 2022/12/03 18:28:11 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_16(unsigned int n, char sign)
{
	int	count;

	if (sign != 'x' && sign != 'X')
		return (0);
	count = 0;
	if (n >= 0 && n <= 9)
		count += ft_putchar(n + 48);
	else if (n >= 10 && n <= 15 && sign == 'x')
		count += ft_putchar(n - 10 + 'a');
	else if (n >= 10 && n <= 15 && sign == 'X')
		count += ft_putchar(n - 10 + 'A');
	else
	{
		count += ft_putnbr_16(n / 16, sign);
		count += ft_putnbr_16(n % 16, sign);
	}
	return (count);
}
