/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <lzito@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:44:21 by lzito             #+#    #+#             */
/*   Updated: 2023/05/28 01:04:29 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

int	ft_heredoc(t_pipex *ppx, int i)
{
	char	*input;
	size_t	limit_len;

	if (!ppx->limiter[i])
	{
		close(ppx->fd_hd[i][0]);
		close(ppx->fd_hd[i][1]);
		return (-1);
	}
	limit_len = ft_strlen(ppx->limiter[i]);
	write(1, "> ", 2);
	input = get_next_line(0);
	while (input && ft_strncmp(input, ppx->limiter[i], limit_len) != 0)
	{
		write(1, "> ", 2);
		write(ppx->fd_hd[i][1], input, ft_strlen(input));
		free(input);
		input = get_next_line(0);
	}
	free(ppx->limiter[i]);
	free(input);
	close(ppx->fd_hd[i][1]);
	return (0);
}

int	redir_quotes(int i, char *line)
{
	if (line[i] == '\'')
	{
		i++;
		while (line[i] != '\'')
		{
			if (line[i++] == '\0')
				return (-1);
		}
	}
	else if (line[i] == '"')
	{
		i++;
		while (line[i] != '"')
		{
			if (line[i++] == '\0')
				return (-1);
		}
	}
	else
	{
		while (line[i] != '\0' && line[i] != ' ')
			i++;
	}
	return (i);
}

void	redir_fill(t_minish *minish, int type, char *res, int i)
{
	if (type == APP_OUT || type == REDIR_OUT)
	{
		minish->ppx.fileout[i] = res;
//		printf("file out n%d = %s\n", i,  minish->ppx.fileout[i]);
		if (type == APP_OUT)
			minish->ppx.app_on[i] = 1;
	}
	else if (type == HERE_DOC)
	{
		minish->ppx.limiter[i] = res;
		minish->ppx.hd_on[i] = 1;
		printf("limiter n%d = %s\n", i,  minish->ppx.limiter[i]);
		minish->ppx.n_cmd--;
	}
	else
	{
		minish->ppx.filein[i] = res;
//		printf("file in n%d = %s\n", i,  minish->ppx.filein[i]);
	}
}

int	deal_with_redir(t_minish *minish, int type, int i)
{
	int			j;
	char		*line;
	char		*res;
	t_content	*node;

	node = malloc(sizeof(struct s_content));
	line = minish->line;
	node->type = type;
	while (line[i] == ' ' || line[i] == '<' || line[i] == '>')
		i++;
	j = i;
	if (line[i] == '\'' || line[i] == '"')
		j++;
	i = redir_quotes(i, line);
	if (i == -1)
		return (i);
	res = ft_substr(&line[j], 0, i - j);
	node->str = res;
	ft_lstadd_back(&minish->lst_line, ft_lstnew(node));
	return (i);
}
