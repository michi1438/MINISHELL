/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_hd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <lzito@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 20:25:58 by lzito             #+#    #+#             */
/*   Updated: 2023/04/19 20:47:00 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

void	ft_checkheredoc(char **av, t_pipex *ppx)
{
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		ppx->hd_on = 1;
		ppx->limiter = av[2];
		if (pipe(ppx->fd_hd) == -1)
		{
			ft_error(av[0], -3);
			exit(EXIT_FAILURE);
		}
	}
	else
		ppx->hd_on = 0;
}

int	ft_heredoc(t_pipex *ppx)
{
	char	*input;
	char	*limiter;
	size_t	limit_len;

	limiter = ft_strjoin(ppx->limiter, "\n");
	if (!limiter)
	{
		close(ppx->fd_hd[0]);
		close(ppx->fd_hd[1]);
		return (-1);
	}
	limit_len = ft_strlen(limiter);
	input = get_next_line(0);
	while (input && ft_strncmp(input, limiter, limit_len) != 0)
	{
		write(ppx->fd_hd[1], input, ft_strlen(input));
		free(input);
		input = get_next_line(0);
	}
	free(limiter);
	free(input);
	close(ppx->fd_hd[1]);
	return (0);
}
