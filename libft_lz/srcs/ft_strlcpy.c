/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 22:22:37 by lzito             #+#    #+#             */
/*   Updated: 2022/10/11 15:42:01 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <string.h>
//#include <stdio.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (src[len])
		len++;
	i = 0;
	if (dstsize > 0)
	{
		while (src[i])
		{
			if (i < dstsize - 1)
				dst[i] = src[i];
			i++;
		}
		if (i < dstsize - 1)
			dst[i] = 0;
		else
			dst[dstsize - 1] = 0;
		return (i);
	}
	return (len);
}

/*
int	main(void)
{
	char	*str_src;
	char	str_dest[10] = "";
	size_t	size;

	str_src = "coucou";
	size = 6;
	printf("%zu\n", ft_strlcpy(str_dest, str_src, size));
	//printf("%lu\n", strlcpy(str_dest, str_src, size));
	return (0);
}
		//printf("%s\n%s\n", src, dest); 
		// a mettre dans le ft_strlcpy a la ligne 38 pour les tests
*/
