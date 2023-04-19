/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:54:33 by lzito             #+#    #+#             */
/*   Updated: 2022/10/18 11:54:39 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len2;

	len2 = ft_strlen(needle);
	if (*needle == 0)
		return ((char *)haystack);
	while (*haystack && len-- >= len2)
	{
		if (*haystack == *needle && ft_strncmp(haystack, needle, len2) == 0)
			return ((char *)haystack);
		haystack++;
	}	
	return (NULL);
}
/*
int	main(void)
{
	char	str[] = "Hello lol yo";
	char	*to_find;

	to_find = "yo";
	printf("%s\n", ft_strnstr(str, to_find, 12));
	printf("%s\n", strnstr(str, to_find, 12));
	return (0);
}
*/
