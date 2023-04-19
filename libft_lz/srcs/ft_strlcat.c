/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:55:35 by lzito             #+#    #+#             */
/*   Updated: 2022/10/14 19:13:56 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i_src;
	size_t	i_dst;
	size_t	i;

	i_dst = ft_strlen(dst);
	i_src = ft_strlen(src);
	i = 0;
	if (dstsize < 1)
		return (i_src);
	while (i_dst + i < dstsize - 1 && src[i])
	{
		dst[i_dst + i] = src[i];
		i++;
	}
	dst[i_dst + i] = 0;
	if (i_dst > dstsize)
		return (i_src + dstsize);
	return (i_dst + i_src);
}
/*
int	main(void)
{
	char	*src;
	char	dest[20] = "Youpi 00000";
	size_t	size;

	src = "hey";
	size = 9;
	printf("%zu\n", ft_strlcat(dest, src, size));
	//printf("%lu\n", strlcat(dest, src, size));
	return (0);
}
	//printf("%s\n%s\n", src, dst); 
	// a mettre dans a la ligne 38 pour les tests
*/
