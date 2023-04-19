/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:16:25 by lzito             #+#    #+#             */
/*   Updated: 2022/10/14 20:41:27 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

char	*ft_strdup(const char *s1)
{
	char	*dest;
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (s1[size] != 0)
		size++;
	dest = malloc(sizeof(*s1) * size + 1);
	if (dest == 0)
		return (NULL);
	while (i <= size)
	{
		dest[i] = s1[i];
		i++;
	}
	return (dest);
}

/*
int	main(void)
{
	char	*src;
   
	src = "1234";
   	//ft_strdup(src);
	printf("%s\n", ft_strdup(src));	
	//printf("%s\n", strdup(src));	
	return (0);
}
	//printf("%lu\n", sizeof(*src) * size + 1);
*/
