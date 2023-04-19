/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:12:14 by lzito             #+#    #+#             */
/*   Updated: 2022/10/19 16:41:54 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*res;

	i = 0;
	start = 0;
	end = ft_strlen(s1);
	while (s1[i] && ft_strchr(set, s1[i++]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	res = malloc(sizeof(*s1) * (end - start + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < end - start)
	{
		res[i] = s1[start + i];
		i++;
	}
	res[i] = 0;
	return (res);
}
/*
int	main(void)
{
	printf("%s\n", ft_strtrim("Hello42", "42"));	
	return (0);
}
*/
