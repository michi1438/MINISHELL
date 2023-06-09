/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_not_tokenable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 16:57:22 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/07 15:15:16 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_not_tokenable(t_minish *minish, int i, const char *tok[])
{
	int			size;
	char		*str;
	t_content	*node;

	node = w_malloc_protect(sizeof(t_content));
	size = not_token_size(minish, i, tok);
	if (size > 0)
	{
		str = ft_substr(&minish->line[i], 0, size);
		if (is_all_space(str) == 1)
		{
			node->str = ft_strtrim(str, " ");
			node->type = OTHER;
			ft_lstadd_back(&minish->lst_line, ft_lstnew(node));
		}
		free(str);
	}
	else
		free(node);
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
		if (tok[j] == NULL || j == OTHER)
		{
			size++;
			i++;
		}
	}
	return (size);
}

int	is_all_space(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}
