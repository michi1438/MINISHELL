/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tokenable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 16:58:36 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/22 19:21:21 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_tokenable(t_minish *minish, int i, const char *tok[])
{
	int	j;

	j = 0;
	while (tok[j] != NULL)
	{
		if (ft_strncmp(&minish->line[i], tok[j], ft_strlen(tok[j])) == 0)
		{
			if (j == 0 || j == 1)
				return (search_quotes(minish, j, i));
			else if (j == 2)
				return (deal_with_pipes(minish, i));
			else if (j == 7)
				return (deal_with_spaces(minish, i));
			else
				return (deal_with_redir(minish, j, i));
		}
		j++;
	}
	return (i);
}

int	search_quotes(t_minish *minish, int type, int i)
{
	int			j;
	char		c;
	char		*line;
	t_content	*node;

	node = malloc(sizeof(struct s_content));
	line = minish->line;
	j = i;
	c = '"';
	node->type = DBLQUOTE;
	if (type == 0)
	{
		node->type = QUOTE;
		c = '\'';
	}		
	i++;
	while (line[i] != c)
	{
		if (line[i] == '\0')
			return (-1);
		i++;
	}
	node->str = ft_substr(&line[j], 0, (i + 1) - j);
	ft_lstadd_back(&minish->lst_line, ft_lstnew(node));
	return (i);
}

int	deal_with_pipes(t_minish *minish, int i)
{
	int			j;
	char		*line;
	t_content	*node;

	node = malloc(sizeof(struct s_content));
	line = minish->line;
	j = i;
	minish->ppx.n_cmd++;
	node->str = ft_substr(&line[j], 0, (i + 1) - j);
	node->type = PIPE;
	ft_lstadd_back(&minish->lst_line, ft_lstnew(node));
	printf("PIPE i = %d\n", i);
	return (i);
}

int	redir_quotes(int i, char *line)
{
	if (line[i] == '\'')
	{
		i++;
		while (line[i] != '\'')
		{
			if (line[i] == '\0')
				return (-1);
			i++;
		}
	}
	else if (line[i] == '"')
	{
		i++;
		while (line[i] != '"')
		{
			if (line[i] == '\0')
				return (-1);
			i++;
		}
	}
	else
	{
		while (line[i] != '\0' && line[i] != ' ')
			i++;
	}
	return (i);
}

int	deal_with_redir(t_minish *minish, int type, int i)
{
	int		j;
	char	*line;
	char	*res;

	line = minish->line;
	while (line[i] == ' ' || line[i] == '<' || line[i] == '>')
		i++;
	j = i;
	if (line[i] == '\'' || line[i] == '"')
		j++;
	i = redir_quotes(i, line);
	if (i == -1)
		res = "exit";
	res = ft_substr(&line[j], 0, i - j);
	if (type == APP_OUT || type == REDIR_OUT)
	{
		minish->ppx.fileout = res;
		if (type == APP_OUT)
			minish->ppx.app_on = 1;
	}
	else if (type == HERE_DOC)
	{
		minish->ppx.limiter = res;
		minish->ppx.hd_on = 1;
	}
	else
		minish->ppx.filein = res;
	printf("RES = %s$\n", res);
	printf("REDIR i = %d\n", i + 1);
	return (i + 1);
}

int	deal_with_spaces(t_minish *minish, int i)
{
	int			j;
	char		*line;
	t_content	*node;

	node = malloc(sizeof(struct s_content));
	line = minish->line;
	j = i;
	node->str = ft_substr(&line[j], 0, (i + 1) - j);
	node->type = SPCE;
	ft_lstadd_back(&minish->lst_line, ft_lstnew(node));
	return (i);
}
