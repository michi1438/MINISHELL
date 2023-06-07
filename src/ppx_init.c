/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:27:08 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/07 17:39:19 by mguerga          ###   ########.fr       */
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
	ppx->fd = w_ft_calloc_prot(ppx->n_cmd, sizeof(int *));
	ppx->pid = w_ft_calloc_prot(ppx->n_cmd, sizeof(int));
	ppx->cmd = w_ft_calloc_prot(ppx->n_cmd, sizeof(char **));
	ppx->path = w_ft_calloc_prot(ppx->n_cmd, sizeof(char *));
	ppx->fd_hd = w_ft_calloc_prot(ppx->n_cmd, sizeof(int *));
	ppx->f_in = w_ft_calloc_prot(ppx->n_cmd, sizeof(int));
	ppx->f_out = w_ft_calloc_prot(ppx->n_cmd, sizeof(int));
	if (ft_initppx_io(ppx) == -1)
		return (-1);
	if (ft_feedppx(ppx, minish->cmds, minish->env) == -1)
		return (-1);
	return (0);
}
