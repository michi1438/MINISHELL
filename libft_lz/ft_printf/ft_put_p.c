/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 11:22:45 by lzito             #+#    #+#             */
/*   Updated: 2022/12/03 18:26:42 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_p(uintptr_t n)
{
	int	count;

	count = 0;
	if (n >= 0 && n <= 9)
		count += ft_putchar(n + 48);
	else if (n >= 10 && n <= 15)
		count += ft_putchar(n - 10 + 'a');
	else
	{
		count += ft_put_p(n / 16);
		count += ft_put_p(n % 16);
	}
	return (count);
}
