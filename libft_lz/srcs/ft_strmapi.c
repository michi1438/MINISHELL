/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:18:07 by lzito             #+#    #+#             */
/*   Updated: 2022/10/25 12:37:50 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/*
char	ft_f(unsigned int i, char c)
{
	i = 1;
	c -= 32;
	return (c);
}
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	size;
	char			*res;

	i = 0;
	size = ft_strlen(s);
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	while (s[i])
	{
		res[i] = f(i, s[i]);
		i++;
	}
	res[i] = 0;
	return (res);
}
/*
int	main(void)
{
	printf("%s\n", ft_strmapi("blabla", &ft_f));
	return (0);
}
*/
