/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:52:13 by lzito             #+#    #+#             */
/*   Updated: 2022/10/14 12:37:54 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h> 
//#include <strings.h> 

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
	/*char	*string;
	string = (char *)s;
	while (n > 0)
	{
		string[n - 1] = 0;
		n--;
	}*/

/*
int	main(void)
{
	char	s[] = "coucou";

	printf("%s\n", s);
	//bzero(s, 3);
	ft_bzero(s, 3);
	printf("%s\n", s);
	return (0);
}
*/
