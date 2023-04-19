/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:57:29 by lzito             #+#    #+#             */
/*   Updated: 2022/10/18 13:13:55 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (str1[i] == str2[i] && i < n)
	{
		if (i == n - 1)
			return (str1[i] - str2[i]);
		i++;
	}
	if (n != 0)
		return (str1[i] - str2[i]);
	else
		return (0);
}
/*
int	main(void)
{
	char	*s1;
	char	*s2;

	s1 = "\x12\xff\x65\x12\xbd\xde\xad";
	s2 = "\x12\x02";
	printf("%d\n", ft_memcmp(s1, s2, 5));
	printf("%d\n", memcmp(s1, s2, 5));
	return (0);
}
*/
