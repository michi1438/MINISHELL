/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:14:25 by lzito             #+#    #+#             */
/*   Updated: 2022/10/18 16:03:27 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;

	i = 0;
	if (!(unsigned char *)src && !(unsigned char *)dst)
		return (NULL);
	if ((unsigned char *)src > (unsigned char *)dst)
	{
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		while (len > 0)
		{
			((unsigned char *)dst)[len - 1] = ((unsigned char *)src)[len - 1];
			len--;
		}
	}
	return ((unsigned char *)dst);
}
/*
int	main(void)
{
	char	dst[] = "zazaza";
	char	src[] = "toto";

	printf("%s, %s\n", dst, src);
	ft_memmove(dst, src, 4);
	printf("%s, %s\n", dst, src);
	return (0);
}
*/
