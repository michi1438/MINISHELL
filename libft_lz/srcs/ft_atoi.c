/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:31:42 by lzito             #+#    #+#             */
/*   Updated: 2022/10/14 15:08:03 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <string.h>
//#include "libft.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	sign = 1;
	res = 0;
	while (*str == ' ' || *str == '\r' || *str == '\f'
		|| *str == '\v' || *str == '\n' || *str == '\t')
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
		if (*str == '+' || *str == '-')
			return (res);
	}
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str - 48);
		str++;
	}
	return (res * sign);
}
/*
int	main(void)
{
	printf("%d\n", atoi("+/+1234"));
	printf("%d\n", ft_atoi("+/+1234"));
	return (0);
}
*/
