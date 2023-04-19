/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <lzito@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 15:05:54 by lzito             #+#    #+#             */
/*   Updated: 2022/12/03 20:32:15 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_gnl_calloc(size_t count, size_t size)
{
	void	*res;
	size_t	i;

	i = 0;
	res = (void *)malloc(size * count);
	if (!res)
		return (NULL);
	while (i < (size * count))
	{
		((unsigned char *)res)[i] = 0;
		i++;
	}
	return (res);
}


void	*ft_clean(char **tofree)
{
	free(*tofree);
	*tofree = NULL;
	return (*tofree);
}

char	*ft_return_line(char **stash, ssize_t red, char endchar)
{
	char	*line;

	line = ft_gnl_substr(*stash, 0, (ft_strlen_plus(*stash, endchar) + 1));
	if (red > 0)
		*stash = ft_strdupchr(*stash);
	else
		ft_clean(stash);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		buf[BUFFER_SIZE + 1];
	ssize_t		red;

	red = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash[fd])
		stash[fd] = ft_gnl_calloc(sizeof(char), 1);
	if (ft_gnl_strchr(stash[fd], '\n'))
		return (ft_return_line(&stash[fd], red, '\n'));
	red = read(fd, buf, BUFFER_SIZE);
	while (red > 0)
	{
		buf[red] = 0;
		stash[fd] = ft_gnl_strjoin(stash[fd], buf);
		if (ft_gnl_strchr(stash[fd], '\n'))
			return (ft_return_line(&stash[fd], red, '\n'));
		red = read(fd, buf, BUFFER_SIZE);
	}
	if (stash[fd][0] && red == 0)
		return (ft_return_line(&stash[fd], red, '\0'));
	return (ft_clean(&stash[fd]));
}
