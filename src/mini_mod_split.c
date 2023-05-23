/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_mod_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:21:55 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/17 16:01:26 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_mod_split(char const *s, char c)
{
	char	**ptrptr;
	int		j;
	int		i[1];

	i[0] = 0;
	ptrptr = malloc((mini_counter(s, c) + 1) * sizeof(ptrptr));
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
	while ((s[i[0]] == c && i[0] == 0) || (s[i[0]] == c && s[i[0] - 1] != '\\'))
		i[0]++;
	while (s[i[0]] != c && s[i[0]] != '\0')
	{
		if (s[i[0]] == '\\' && s[i[0] + 1] == c)
		{
			i[0]++;
			space++;
		}
		buf++;
		i[0]++;
	}
	*ptrptr = malloc((buf + 1) * sizeof(char));
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