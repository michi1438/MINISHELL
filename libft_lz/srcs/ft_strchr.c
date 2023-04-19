/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:50:12 by lzito             #+#    #+#             */
/*   Updated: 2022/12/03 20:20:26 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	target;
	int		i;
	char	*src;

	target = (char)c;
	src = (char *)s;
	i = 0;
	while (src[i])
	{
		if (src[i] == target)
			return (&src[i]);
		i++;
	}
	if (src[i] == target)
		return (&src[i]);
	return (NULL);
}
