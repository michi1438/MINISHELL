/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr_rev.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 20:55:29 by lzito             #+#    #+#             */
/*   Updated: 2023/03/09 14:08:55 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	min;

	min = -2147483648;
	if (n >= 0 && n <= 9)
		ft_putchar_fd(n + 48, fd);
	else if (n == min)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd((n % 10) * -1, fd);
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

int	main(void)
{
	ft_putnbr_fd(0, 1);
	return (0);
}
