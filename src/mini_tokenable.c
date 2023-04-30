/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tokenable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 16:58:36 by mguerga           #+#    #+#             */
/*   Updated: 2023/04/30 16:58:39 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_tokenable(t_minish *minish, int i, const char *tok[])
{
	int		j;

	j = 0;
	while (tok[j] != NULL)
	{
		if (ft_strncmp(&minish->line[i], tok[j], ft_strlen(tok[j])) == 0)
		{
			if (j == 0 || j == 1)
				return (search_quotes(minish->line, j, i));
			else if (j == 2)
				return (deal_with_pipes(minish, i));
			else if (j <= 6 && j >= 3)
				return (deal_with_redir(minish->line, j, i));
			else
				return (deal_with_other(minish->line, j, i));
		}
		j++;
	}
	return (i);
}

int	search_quotes(char *line, int type, int i)
{
	int		j;
	char	c;

	j = i;
	c = '"';
	if (type == 0)
		c = '\'';
	i++;
	while (line[i] != c)
	{
		if (line[i] == '\0')
			return (-1);
		i++;
	}
	printf("%s\n", ft_substr(&line[j], 0, (i + 1) - j));
	return (i);
}

int	deal_with_pipes(t_minish *minish, int i)
{
	minish->n_cmd++;
	printf("|\n");
	return (i);
}

int	deal_with_redir(char *line, int type, int i)
{
	int	j;

	j = i;
	if (type < 5)
		i++;
	printf("%s\n", ft_substr(&line[j], 0, (i + 1) - j));
	return (i);
}

int	deal_with_other(char *line, int type, int i)
{
	int		j;

	(void)type;
	j = i;
	while (line[i] != ' ' && line[i] != '\0')
		i++;
	printf("TO EXPAND :%s\n", ft_substr(&line[j], 0, (i + 1) - j));
	return (i);
}
