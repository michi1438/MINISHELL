/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_init_add_cmds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:49:04 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/07 16:02:30 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_cmds(t_minish *minish)
{
	minish->cmds = gc_malloc(minish->ppx.n_cmd * sizeof(char *));
	minish->ppx.limiter = gc_malloc(minish->ppx.n_cmd * sizeof(char *));
	minish->ppx.hd_on = gc_malloc(minish->ppx.n_cmd * sizeof(int));
	minish->ppx.filein = gc_malloc(minish->ppx.n_cmd * sizeof(char *));
	minish->ppx.fileout = gc_malloc(minish->ppx.n_cmd * sizeof(char *));
	minish->ppx.app_on = gc_malloc(minish->ppx.n_cmd * sizeof(int));
	return (0);
}

void	add_cmds(t_minish *minish)
{
	t_list		*lst;
	t_content	*cont;
	int			i;

	lst = minish->lst_line;
	init_cmds(minish);
	i = 0;
	while (lst != NULL)
	{
		cont = lst->content;
		words_concat(cont, minish, i);
		if (cont->type >= APP_OUT && cont->type <= REDIR_IN)
		{
			if (ft_strncmp(cont->str, "", 1) != 0)
				add_redirs(cont, minish, i);
			else
				cont->str = NULL;
		}
		else if (cont->type == PIPE && minish->cmds[i] != NULL)
			i++;
		lst = lst->next;
	}
}

void	add_redirs(t_content *cont, t_minish *minish, int i)
{
	char		*temp;

	temp = ft_strdup(cont->str);
	free(cont->str);
	redir_fill(minish, cont->type, temp, i);
	cont->str = ft_strdup("");
	append_or_start(minish, cont->str, NULL, i);
}

void	words_concat(t_content *cont, t_minish *minish, int i)
{
	if (cont->type == OTHER)
	{
		cont->str = expand_variables(cont->str, minish);
		append_or_start(minish, cont->str, NULL, i);
	}
	else if (cont->type == QUOTE)
	{
		cont->str = expand_variables(cont->str, minish);
		append_or_start(minish, cont->str, "'", i);
	}
	else if (cont->type == DBLQUOTE)
	{
		cont->str = expand_variables(cont->str, minish);
		append_or_start(minish, cont->str, "\"", i);
	}
	else if (cont->type == SPCE)
		append_or_start(minish, cont->str, NULL, i);
}
