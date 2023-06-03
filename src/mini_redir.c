/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <lzito@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:44:21 by lzito             #+#    #+#             */
/*   Updated: 2023/06/03 04:29:28 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_heredoc(t_pipex *ppx, int i)
{
	char	*input;
	size_t	limit_len;

	ft_signals_n_attr(HD);
	limit_len = ft_strlen(ppx->limiter[i]);
	write(1, "> ", 2);
	input = get_next_line(0);
	if (!input && g_exit_status != 130)
		write(1, "\n", 1);
	while (g_exit_status != 130 && input 
		&& ft_strncmp(input, ppx->limiter[i], limit_len) != 0)
	{
		write(1, "> ", 2);
		write(ppx->fd_hd[i][1], input, ft_strlen(input));
		free(input);
		input = get_next_line(0);
		if (!input && g_exit_status != 130)
			write(1, "\n", 1);
	}
	ft_signals_n_attr(RESET);
	//TODO	free(ppx->limiter[i]);
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
		if (type == APP_OUT)
			minish->ppx.app_on[i] = 1;
	}
	else if (type == HERE_DOC)
	{
		minish->ppx.limiter[i] = res;
		minish->ppx.hd_on[i] = 1;
	}
	else
		minish->ppx.filein[i] = res;
}

int	deal_with_redir(t_minish *minish, int type, int i)
{
	int			j;
	char		*line;
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
	node->str = ft_substr(&line[j], 0, i - j);
	printf("cont->str added = %p, %s$\n", node->str, node->str);
	printf("node added = %p\n", node);
	ft_lstadd_back(&minish->lst_line, ft_lstnew(node));
	return (i);
}
