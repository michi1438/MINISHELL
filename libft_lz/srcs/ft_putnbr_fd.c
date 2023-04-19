/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 20:55:29 by lzito             #+#    #+#             */
/*   Updated: 2022/10/14 19:20:34 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	min;

	min = -2147483648;
	if (n >= 0 && n <= 9)
		ft_putchar_fd(n + 48, fd);
	else if (n == min)
	{
		ft_putnbr_fd(min / 10, fd);
		ft_putnbr_fd(min % 10 * -1, fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(n * -1, fd);
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}
/*
int	main(void)
{
	ft_putnbr_fd(1234, 1);
	return (0);
}
*/
