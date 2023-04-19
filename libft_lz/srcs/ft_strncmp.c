/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:30:42 by lzito             #+#    #+#             */
/*   Updated: 2022/10/14 15:50:17 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (str1[i] != 0 && str1[i] == str2[i])
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
	printf("%d\n", ft_strncmp(s1, s2, 5));
	printf("%d\n", strncmp(s1, s2, 5));
	return (0);
}
*/
