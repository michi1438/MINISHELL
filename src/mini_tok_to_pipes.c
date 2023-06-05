/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tok_to_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:33:23 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/05 14:38:15 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_cmds(t_minish *minish)
{
	//TODO MALLOC A PROTEGER !!!
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
	char		*temp;

	lst = minish->lst_line;
	init_cmds(minish);
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
		{
			cont->str = expand_variables(cont->str, minish);
			append_or_start(minish, cont->str, "'", i);
		}
		else if (cont->type == DBLQUOTE)
		{
			cont->str = expand_variables(cont->str, minish);
			append_or_start(minish, cont->str, "\"", i);
		}
		else if (cont->type >= APP_OUT && cont->type <= REDIR_IN)
		{
			if (ft_strncmp(cont->str, "", 1) != 0)
			{
				temp = ft_strdup(cont->str);
				free(cont->str);
				redir_fill(minish, cont->type, temp, i);
				cont->str = ft_strdup("");
				append_or_start(minish, cont->str, NULL, i);
			}
			else
				cont->str = NULL;
		}
		else if (cont->type == SPCE)
			append_or_start(minish, cont->str, NULL, i);
		else if (cont->type == PIPE && minish->cmds[i] != NULL)
			i++;
		lst = lst->next;
	}
}

void	append_or_start(t_minish *minish, char *strseg, char *tok_delimiter, int i)
{
	char	*temp;

	if (minish->cmds[i] == NULL)
	{
		if (tok_delimiter == NULL)
		{
			if (is_all_space(strseg) == 0)
				minish->cmds[i] = ft_strdup(" ");
			else
				minish->cmds[i] = ft_strdup(strseg);
		}
		else
			minish->cmds[i] = ft_strtrim(strseg, tok_delimiter);
	}
	else
	{
		if (tok_delimiter == NULL)
		{
			if (is_all_space(strseg) == 0)
				minish->cmds[i] = w_strjoin_rm_arg1(minish->cmds[i], " ");
			else
				minish->cmds[i] = w_strjoin_rm_arg1(minish->cmds[i], strseg);
		}
		else
		{
			temp = ft_strtrim(strseg, tok_delimiter);
			minish->cmds[i] = w_strjoin_rm_arg1(minish->cmds[i], temp);
			free(temp);
		}
	}
}
