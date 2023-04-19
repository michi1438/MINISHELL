/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:49:12 by lzito             #+#    #+#             */
/*   Updated: 2022/10/19 21:05:33 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_n_len(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		n_len;
	long	nb;

	nb = n;
	n_len = ft_n_len(nb);
	res = malloc(sizeof(char) * (n_len + 1));
	if (!res)
		return (NULL);
	res[n_len--] = 0;
	if (nb == 0)
		res[0] = 48;
	if (nb < 0)
	{
		res[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		res[n_len] = (nb % 10) + 48;
		nb /= 10;
		n_len--;
	}
	return (res);
}
/*
int	main(void)
{
	printf("%s\n", ft_itoa(0));
	return (0);
}
*/
