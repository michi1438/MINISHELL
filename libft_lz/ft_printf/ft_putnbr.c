/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 21:12:27 by lzito             #+#    #+#             */
/*   Updated: 2022/12/03 18:27:57 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(long int n)
{
	int	count;

	count = 0;
	if (n >= 0 && n <= 9)
		count += ft_putchar(n + 48);
	else if (n < 0)
	{
		count += ft_putchar('-');
		count += ft_putnbr(n * -1);
	}
	else
	{
		count += ft_putnbr(n / 10);
		count += ft_putnbr(n % 10);
	}
	return (count);
}
