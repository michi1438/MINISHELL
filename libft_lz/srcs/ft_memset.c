/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:55:44 by lzito             #+#    #+#             */
/*   Updated: 2022/10/14 11:45:02 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	value;
	char			*str;
	size_t			i;

	value = (unsigned char)c;
	str = (char *)b;
	i = 0;
	while (i < len)
		str[i++] = value;
	return (str);
}
/*
int	main(void)
{
	char	str[] = "Hello";

	printf("%s\n", str);
	ft_memset(str, 'Z', 3);
	//memset(str, 'Z', 3);
	printf("%s\n", str);
	return (0);
}
*/
