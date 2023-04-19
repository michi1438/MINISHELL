/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <lzito@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 15:03:04 by lzito             #+#    #+#             */
/*   Updated: 2022/12/03 20:32:35 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_gnl_strchr(const char *s, int c)
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
			return (&src[i + 1]);
		i++;
	}
	if (src[i] == target)
		return (&src[i + 1]);
	return (NULL);
}

char	*ft_strdupchr(char *s1)
{
	char	*dest;
	char	*rest_line;
	int		i;
	int		size;

	rest_line = ft_gnl_strchr(s1, '\n');
	if (!rest_line)
		return (NULL);
	i = 0;
	size = ft_strlen_plus(rest_line, '\0');
	dest = ft_gnl_calloc(sizeof(*rest_line), size + 1);
	if (!dest)
		return (NULL);
	while (i <= size)
	{
		dest[i] = rest_line[i];
		i++;
	}
	ft_clean(&s1);
	return (dest);
}

char	*ft_gnl_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	unsigned int	s_len;
	char			*res;

	i = 0;
	s_len = ft_strlen_plus(s, '\0');
	if (start >= s_len)
		len = 0;
	if (len > s_len)
		len = s_len - start;
	res = ft_gnl_calloc(sizeof(char), (len + 1));
	if (!res)
		return (NULL);
	while (i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	s1_len;
	size_t	s2_len;
	char	*res;

	i = 0;
	j = 0;
	s1_len = ft_strlen_plus(s1, '\0');
	s2_len = ft_strlen_plus(s2, '\0');
	res = ft_gnl_calloc(sizeof(char), (s1_len + s2_len) + 1);
	if (!res)
		return (NULL);
	while (i < s1_len)
	{
		res[i] = s1[i];
		i++;
	}
	while (j < s2_len)
		res[i++] = s2[j++];
	res[i] = 0;
	ft_clean(&s1);
	return (res);
}

size_t	ft_strlen_plus(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c)
		i++;
	return (i);
}
