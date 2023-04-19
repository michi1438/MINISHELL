/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <lzito@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 15:05:03 by lzito             #+#    #+#             */
/*   Updated: 2022/12/03 20:31:14 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../srcs/libft.h"
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*get_next_line(int fd);
void	*ft_clean(char **tofree);
char	*ft_strdupchr(char *s1);
void	*ft_gnl_calloc(size_t count, size_t size);
char	*ft_gnl_strchr(const char *s, int c);
char	*ft_gnl_strjoin(char *s1, char *s2);
size_t	ft_strlen_plus(const char *s, char c);
char	*ft_gnl_substr(char const *s, unsigned int start, size_t len);

#endif
