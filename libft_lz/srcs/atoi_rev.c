/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_rev.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:31:42 by lzito             #+#    #+#             */
/*   Updated: 2023/03/09 12:59:46 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

int	ft_iisspace(const char c)
{
	if (c == ' ' || c == '\n' || c == '\r' || c == '\v' || c == '\t'
			|| c == '\f')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (ft_iisspace(*str))
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
		if (*str == '-' || *str	== '+')
			return (res);
	}
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str - 48);
		str++;
	}
	return (res * sign);
}

int	main(void)
{
	printf("%d\n", atoi("+1234"));
	printf("%d\n", ft_atoi("+1234"));
	return (0);
}
