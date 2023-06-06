/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_append_or_start.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:50:11 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/06 14:50:42 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_or_start(t_minish *minish, char *strseg, char *delim, int i)
{
	if (minish->cmds[i] == NULL)
	{
		if (delim == NULL)
		{
			if (is_all_space(strseg) == 0)
				minish->cmds[i] = ft_strdup(" ");
			else
				minish->cmds[i] = ft_strdup(strseg);
		}
		else
			minish->cmds[i] = ft_strtrim(strseg, delim);
	}
	else
		append(minish, strseg, delim, i);
}

void	append(t_minish *minish, char *strseg, char *delim, int i)
{
	char	*temp;

	if (delim == NULL)
	{
		if (is_all_space(strseg) == 0)
			minish->cmds[i] = w_strjoin_rm_arg1(minish->cmds[i], " ");
		else
			minish->cmds[i] = w_strjoin_rm_arg1(minish->cmds[i], strseg);
	}
	else
	{
		temp = ft_strtrim(strseg, delim);
		minish->cmds[i] = w_strjoin_rm_arg1(minish->cmds[i], temp);
		free(temp);
	}
}
