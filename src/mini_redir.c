/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <lzito@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:44:21 by lzito             #+#    #+#             */
/*   Updated: 2023/05/25 13:39:07 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

int	ft_heredoc(t_pipex *ppx)
{
	char	*input;
	size_t	limit_len;

	if (!ppx->limiter)
	{
		close(ppx->fd_hd[0]);
		close(ppx->fd_hd[1]);
		return (-1);
	}
	limit_len = ft_strlen(ppx->limiter);
	write(1, "> ", 2);
	input = get_next_line(0);
	while (input && ft_strncmp(input, ppx->limiter, limit_len) != 0)
	{
		write(1, "> ", 2);
		write(ppx->fd_hd[1], input, ft_strlen(input));
		free(input);
		input = get_next_line(0);
	}
	free(ppx->limiter);
	free(input);
	close(ppx->fd_hd[1]);
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

void	redir_fill(t_minish *minish, int type, char *res)
{
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
		minish->ppx.n_cmd--;
	}
	else
		minish->ppx.filein = res;
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
		return (i);
	res = ft_substr(&line[j], 0, i - j);
	redir_fill(minish, type, res);
	return (i);
}
