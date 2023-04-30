/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_not_tokenable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 16:57:22 by mguerga           #+#    #+#             */
/*   Updated: 2023/04/30 16:58:07 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_not_tokenable(t_minish *minish, int i, const char *tok[])
{
	int		size;
	char	*str;

	size = not_token_size(minish, i, tok);
	if (size > 0)
	{
		str = ft_substr(&minish->line[i], 0, size);
		printf("%s\n", ft_strtrim(str, " "));
	}
	return (i + size);
}	

int	not_token_size(t_minish *minish, int i, const char *tok[])
{
	int		size;
	int		j;

	size = 0;
	while (minish->line[i] != '\0')
	{
		j = 0;
		while (tok[j] != NULL)
		{
			if (ft_strncmp(&minish->line[i], tok[j], ft_strlen(tok[j])) == 0)
			{
				return (size);
			}
			else
				j++;
		}
		if (tok[j] == NULL || j == 8)
		{
			size++;
			i++;
		}
	}
	return (size);
}
