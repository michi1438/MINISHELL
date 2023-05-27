/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <lzito@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 01:05:27 by lzito             #+#    #+#             */
/*   Updated: 2023/05/28 01:06:06 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_redir_only_cmd(t_pipex *ppx, int idx)
{
	if (ppx->hd_on[idx] == 0)
		ft_dup(ppx->f_in[idx], ppx->f_out[idx]);
	else
		ft_dup(ppx->fd_hd[idx][0], ppx->f_out[idx]);
}

void	ft_redir_first_cmd(t_pipex *ppx, int idx)
{
	if (ppx->hd_on[idx] == 0)
	{
		if (ppx->fileout[idx] == NULL)
			ft_dup(ppx->f_in[idx], ppx->fd[idx][1]);
		else
			ft_dup(ppx->f_in[idx], ppx->f_out[idx]);
	}
	else
	{
		if (ppx->fileout[idx] == NULL)
			ft_dup(ppx->fd_hd[idx][0], ppx->fd[idx][1]);
		else
			ft_dup(ppx->fd_hd[idx][0], ppx->f_out[idx]);
	}
}

void	ft_redir_mid_cmd(t_pipex *ppx, int idx)
{
	if (ppx->hd_on[idx] == 0)
	{
		if (ppx->filein[idx] == NULL)
		{
			if (ppx->fileout[idx] == NULL)
				ft_dup(ppx->fd[idx - 1][0], ppx->fd[idx][1]);
			else
				ft_dup(ppx->fd[idx - 1][0], ppx->f_out[idx]);
		}
		else
		{
			if (ppx->fileout[idx] == NULL)
				ft_dup(ppx->f_in[idx], ppx->fd[idx][1]);
			else
				ft_dup(ppx->f_in[idx], ppx->f_out[idx]);
		}
	}
	else
	{
		if (ppx->fileout[idx] == NULL)
			ft_dup(ppx->fd_hd[idx][0], ppx->fd[idx][1]);
		else
			ft_dup(ppx->fd_hd[idx][0], ppx->f_out[idx]);
	}
}

void	ft_redir_last_cmd(t_pipex *ppx, int idx)
{
	if (ppx->hd_on[idx] == 0)
	{
		if (ppx->filein[idx] == NULL)
			ft_dup(ppx->fd[idx - 1][0], ppx->f_out[idx]);
		else
			ft_dup(ppx->f_in[idx], ppx->f_out[idx]);
	}
	else
		ft_dup(ppx->fd_hd[idx][0], ppx->f_out[idx]);
}
