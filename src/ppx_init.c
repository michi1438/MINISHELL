/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:27:08 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/07 17:18:24 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_initppx_io(t_pipex *ppx)
{
	int	i;

	i = 0;
	while (i < ppx->n_cmd)
	{
		if (ppx->filein[i] == NULL)
			ppx->f_in[i] = 0;
		if (ppx->fileout[i] == NULL)
			ppx->f_out[i] = 1;
		if (ppx->fileout[i] != NULL)
		{
			ppx->f_out[i] = init_f_out(ppx, i);
			if (ppx->f_out[i] == -1)
				return (ft_error(ppx->fileout[i], -1));
		}
		if (ppx->hd_on[i] == 0 && ppx->filein[i] != NULL)
		{
			ppx->f_in[i] = open(ppx->filein[i], O_RDONLY);
			if (ppx->f_in[i] == -1)
				return (ft_error(ppx->filein[i], -1));
		}
		i++;
	}
	return (0);
}

int	init_f_out(t_pipex *ppx, int i)
{
	int	ret;

	if (ppx->app_on[i] == 0)
		ret = open(ppx->fileout[i], O_CREAT | O_WRONLY | O_TRUNC, 00644);
	else
		ret = open(ppx->fileout[i], O_CREAT | O_APPEND | O_WRONLY, 00644);
	return (ret);
}

int	ft_initppx(t_pipex *ppx, t_minish *minish)
{
	int	ret;

	ppx->fd = ft_calloc(ppx->n_cmd, sizeof(int *));
	if (ppx->fd == NULL)
		return (ft_error(minish->cmds[0], -1));
	ppx->pid = ft_calloc(ppx->n_cmd, sizeof(int));
	if (ppx->pid == NULL)
		return (ft_error(minish->cmds[0], -1));
	ppx->cmd = ft_calloc(ppx->n_cmd, sizeof(char **));
	if (ppx->cmd == NULL)
		return (ft_error(minish->cmds[0], -1));
	ppx->path = ft_calloc(ppx->n_cmd, sizeof(char *));
	if (ppx->path == NULL)
		return (ft_error(minish->cmds[0], -1));
	ret = ft_initppx_p2(ppx, minish);
	if (ret != 0)
		return (ret);
	return (0);
}

int	ft_initppx_p2(t_pipex *ppx, t_minish *minish)
{
	ppx->fd_hd = ft_calloc(ppx->n_cmd, sizeof(int *));
	if (ppx->fd_hd == NULL)
		return (ft_error(minish->cmds[0], -1));
	ppx->f_in = ft_calloc(ppx->n_cmd, sizeof(int));
	if (ppx->f_in == NULL)
		return (ft_error(minish->cmds[0], -1));
	ppx->f_out = ft_calloc(ppx->n_cmd, sizeof(int));
	if (ppx->f_out == NULL)
		return (ft_error(minish->cmds[0], -1));
	if (ft_initppx_io(ppx) == -1)
		return (-1);
	if (ft_feedppx(ppx, minish->cmds, minish->env) == -1)
		return (-1);
	return (0);
}
