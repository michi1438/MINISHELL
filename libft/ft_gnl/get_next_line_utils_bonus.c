/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbeheydt <xbeheydt@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:05:04 by xbeheydt          #+#    #+#             */
/*   Updated: 2023/04/18 22:47:23 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ptr = ft_calloc(sizeof(char), (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (ptr == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*freeandreplace(char *oldstr, char *stradd, int ind)
{
	char	*nptr;

	if (ind >= 0)
	{
		nptr = ft_strjoin("", &stradd[ind + 1]);
		if (oldstr != NULL)
		{
			free(oldstr);
			oldstr = NULL;
		}
		return (nptr);
	}
	else
	{
		nptr = ft_strjoin(oldstr, stradd);
		free (oldstr);
		return (nptr);
	}
}

int	readforterm(char *buf, int toggle)
{
	int	i;

	i = 0;
	if (toggle == 1)
	{
		while (buf[i] != '\0')
		{
			if (buf[i] == '\n')
				return (i);
			i++;
		}
		return (-1);
	}
	else
	{
		i = 0;
		while (i < BUFFER_SIZE)
		{
			if (buf[i] == '\n' || buf[i] == '\0')
				return (i);
			i++;
		}
		return (-1);
	}
}
