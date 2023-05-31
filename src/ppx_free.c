/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <lzito@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 20:23:44 by lzito             #+#    #+#             */
/*   Updated: 2023/05/31 14:25:10 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_freeall(t_pipex *ppx)
{
	int	i;

	i = 0;
	while (i < ppx->n_cmd)
	{
		if (ppx->cmd != NULL && ppx->cmd[i] != NULL)
			ft_free(ppx->cmd[i]);
		if (ppx->path != NULL && ppx->path[i] != NULL)
			free(ppx->path[i]);
		if (ppx->fd != NULL && ppx->fd[i] != NULL)
			free(ppx->fd[i]);
		if (ppx->fd_hd != NULL && ppx->fd_hd[i] != NULL)
			free(ppx->fd_hd[i]);
		i++;
	}
	if (ppx->cmd != NULL)
		free(ppx->cmd);
	if (ppx->path != NULL)
		free(ppx->path);
	if (ppx->pid != NULL)
		free(ppx->pid);
	if (ppx->fd != NULL)
		free(ppx->fd);
	if (ppx->fd_hd != NULL)
		free(ppx->fd_hd);
}

void	ft_free(char **av)
{
	int	i;

	i = 0;
	if (av != NULL)
	{
		while (av[i])
		{
			free(av[i]);
			i++;
		}
		free(av);
	}
}

int	ft_waitnclose(t_pipex *ppx)
{
	int	i;
	int	wstatus;
	int	statuscode;

	i = 0;
	statuscode = 0;
	while (i < ppx->n_cmd)
	{
		close(ppx->fd[i][0]);
		close(ppx->fd[i][1]);
		if (ppx->filein[i] != NULL)
			close(ppx->f_in[i]);
		if (ppx->fileout[i] != NULL)
			close(ppx->f_out[i]);
		if (ppx->hd_on[i] == 1)
			close(ppx->fd_hd[i][0]);
		waitpid(ppx->pid[i], &wstatus, 0);
		if (ppx->cmd[i][0] != NULL && is_prefork_builtin(ppx->cmd[i]) == 0)
			statuscode = ppx->exit_status;
		else if (WIFEXITED(wstatus))
			statuscode = WEXITSTATUS(wstatus);
		i++;
	}
	ft_freeall(ppx);
	return (statuscode);
}

void	ft_close_fds(t_pipex *ppx)
{
	int	i;

	i = 0;
	while (i < ppx->n_cmd)
	{
		close(ppx->fd[i][0]);
		close(ppx->fd[i][1]);
		if (ppx->filein[i] != NULL)
			close(ppx->f_in[i]);
		if (ppx->fileout[i] != NULL)
			close(ppx->f_out[i]);
		if (ppx->hd_on[i] == 1)
			close(ppx->fd_hd[i][0]);
		i++;
	}
}
