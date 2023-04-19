/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:06:38 by lzito             #+#    #+#             */
/*   Updated: 2022/10/14 14:05:15 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	char	target;
	int		len;
	char	*src;

	target = (char)c;
	src = (char *)s;
	len = 0;
	while (src[len])
		len++;
	if (src[len] == target)
		return (&src[len]);
	while (len >= 0)
	{
		if (src[len] == target)
			return (&src[len]);
		len--;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	s[] = "abbbbbbbbbb";
	char	c = 'a';

	printf("%s\n", ft_strrchr(s, c));
	printf("%s\n", strrchr(s, c));
	return (0);
}
*/
