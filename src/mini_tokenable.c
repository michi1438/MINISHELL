/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tokenable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 16:58:36 by mguerga           #+#    #+#             */
/*   Updated: 2023/04/30 20:22:20 by mguerga          ###   ########.fr       */
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
				return (search_quotes(minish, j, i));
			else if (j == 2)
				return (deal_with_pipes(minish, i));
			else if (j <= 6 && j >= 3)
				return (deal_with_redir(minish, j, i));
			else
				return (deal_with_other(minish, j, i));
		}
		j++;
	}
	return (i);
}

int	search_quotes(t_minish *minish, int type, int i)
{
	int		j;
	char	c;
	char	*line;
	char	*lst_line;

	line = minish->line;
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
	lst_line = ft_substr(&line[j], 0, (i + 1) - j);
	ft_lstadd_back(minish->lst_line, ft_lstnew(lst_line));
	return (i);
}

int	deal_with_pipes(t_minish *minish, int i)
{
	char	*lst_line;

	lst_line = "|";
	minish->n_cmd++;
	ft_lstadd_back(minish->lst_line, ft_lstnew(lst_line));
	return (i);
}

int	deal_with_redir(t_minish *minish, int type, int i)
{
	int		j;
	char	*lst_line;
	char	*line;

	line = minish->line;
	j = i;
	if (type < 5)
		i++;
	lst_line = ft_substr(&line[j], 0, (i + 1) - j);
	ft_lstadd_back(minish->lst_line, ft_lstnew(lst_line));
	return (i);
}

int	deal_with_other(t_minish *minish, int type, int i)
{
	int		j;
	char	*line;
	char	*lst_line;

	line = minish->line;
	(void)type;
	j = i;
	while (line[i] != ' ' && line[i] != '\0')
		i++;
	lst_line = ft_substr(&line[j], 0, (i + 1) - j);
	ft_lstadd_back(minish->lst_line, ft_lstnew(lst_line));
	return (i);
}
