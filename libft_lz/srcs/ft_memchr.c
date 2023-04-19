/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:03:12 by lzito             #+#    #+#             */
/*   Updated: 2022/10/18 12:55:24 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*src;
	unsigned char	target;
	size_t			i;

	src = (unsigned char *)s;
	target = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (src[i] == target)
			return (&src[i]);
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	s[] = "coucou";
	char	c = '0';

	printf("%s\n", ft_memchr(s, c, 3));
	printf("%s\n", memchr(s, c, 3));
	return (0);
}
*/
