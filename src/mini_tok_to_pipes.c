/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tok_to_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:33:23 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/11 18:35:25 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_cmds(t_minish *minish)
{
	t_list		*lst;
	t_content	*cont;
	int			i;

	lst = minish->lst_line;
	minish->cmds = ft_calloc(minish->ppx.n_cmd, sizeof(char *));
	i = 0;
	while (lst != NULL)
	{
		cont = lst->content;
		if (cont->type == OTHER)
		{
			cont->str = expand_variables(cont->str, minish);
			append_or_start(minish, cont->str, NULL, i);
		}
		else if (cont->type == QUOTE)
			append_or_start(minish, cont->str, "'", i);
		else if (cont->type == DBLQUOTE)
		{
			cont->str = expand_variables(cont->str, minish);
			append_or_start(minish, cont->str, "\"", i);
		}
		else
			i++;
		lst = lst->next;
	}
}

void	append_or_start(t_minish *minish, char *strseg, char *tok_delimiter, int i)
{
	if (minish->cmds[i] == NULL)
	{
		if (tok_delimiter == NULL)
			minish->cmds[i] = strseg;
		else
			minish->cmds[i] = ft_strtrim(strseg, tok_delimiter);
	}
	else
	{
		if (tok_delimiter == NULL)
		{
			minish->cmds[i] = ft_strjoin(minish->cmds[i], " ");
			minish->cmds[i] = ft_strjoin(minish->cmds[i], strseg);
		}
		else
		{
			minish->cmds[i] = ft_strjoin(minish->cmds[i], " ");
			minish->cmds[i] = ft_strjoin(minish->cmds[i], ft_strtrim(strseg, tok_delimiter));
		}
	}
}
