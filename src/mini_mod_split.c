/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_mod_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:21:55 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/07 15:51:01 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_mod_split(char const *s, char c)
{
	char	**ptrptr;
	int		j;
	int		i[1];

	i[0] = 0;
	ptrptr = w_malloc_protect((mini_counter(s, c) + 1) * sizeof(ptrptr));
	if (ptrptr == NULL)
		return (NULL);
	j = 0;
	while (j < (mini_counter(s, c)))
	{
		if (mini_implfing(s, c, &(ptrptr[j]), i) == NULL)
			if (mini_clear_fing(ptrptr, j) == 0)
				return (NULL);
		j++;
	}
	ptrptr[j] = NULL;
	return (ptrptr);
}

int	mini_clear_fing(char **ptrptr, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free (ptrptr[i]);
		i++;
	}
	free(ptrptr);
	return (0);
}

void	*mini_implfing(char const *s, char c, char **ptrptr, int *i)
{
	int	e;
	int	buf;
	int	space;

	buf = 0;
	space = 0;
	count_spaces_n_buf(s, i, &buf, &space);
	*ptrptr = w_malloc_protect((buf + 1) * sizeof(char));
	if (*ptrptr == NULL)
		return (NULL);
	i[0] -= buf + space;
	e = 0;
	while (s[i[0]] != c && s[i[0]] != '\0')
	{
		if (s[i[0]] == '\\' && s[i[0] + 1] == c)
			i[0]++;
		(*ptrptr)[e++] = s[i[0]++];
	}
	(*ptrptr)[e] = '\0';
	return (*ptrptr);
}

void	count_spaces_n_buf(const char *s, int *i, int *buf, int *space)
{
	char	c;

	c = ' ';
	while ((s[i[0]] == c && i[0] == 0)
		|| (s[i[0]] == c && s[i[0] - 1] != '\\'))
		i[0]++;
	while (s[i[0]] != c && s[i[0]] != '\0' && (*buf)++ != -1)
	{
		if (s[i[0]] == '\\' && s[i[0]++ + 1] == c)
			(*space)++;
		i[0]++;
	}
}

int	mini_counter(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while ((s[i] == c && i == 0) || (s[i] == c && s[i - 1] != '\\'))
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			if (s[i] == '\\' && s[i + 1] == c)
				i++;
			i++;
		}
		if (s[i - 1] != c || (s[i - 1] == c && s[i - 2] == '\\'))
		{
			count++;
			if (s[i] != '\0')
				i++;
		}
	}
	return (count);
}
