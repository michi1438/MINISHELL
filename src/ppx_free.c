/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <lzito@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 20:23:44 by lzito             #+#    #+#             */
/*   Updated: 2023/06/04 16:06:43 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_freeloop(t_pipex *ppx)
{
	int	i;

	i = 0;
	while (i < ppx->n_cmd)
	{
		printf("ppx->cmd %p, %s$\n", ppx->cmd, ppx->cmd[i][0]);
		if (ppx->cmd != NULL && ppx->cmd[i] != NULL)
			ft_free(ppx->cmd[i]);
		if (ppx->path != NULL && ppx->path[i] != NULL)
			free(ppx->path[i]);
		if (ppx->fd != NULL && ppx->fd[i] != NULL)
			free(ppx->fd[i]);
		if (ppx->fd_hd != NULL && ppx->fd_hd[i] != NULL)
			free(ppx->fd_hd[i]);
		if (ppx->filein != NULL && ppx->filein[i] != NULL)
			free(ppx->filein[i]);
		if (ppx->fileout != NULL && ppx->fileout[i] != NULL)
			free(ppx->fileout[i]);
		if (ppx->limiter != NULL && ppx->limiter[i] != NULL)
			free(ppx->limiter[i]);
		i++;
	}
}

void	ft_freeall(t_pipex *ppx)
{
	ft_freeloop(ppx);
//	printf("ppx->cmd freed %p, %s$\n", ppx->cmd, ppx->cmd[0][0]);
	if (ppx->cmd != NULL)
		free(ppx->cmd);
	if (ppx->path != NULL)
		free(ppx->path);
	if (ppx->pid != NULL)
		free(ppx->pid);
	if (ppx->fd != NULL)
		free(ppx->fd);
	if (ppx->f_in != NULL)
		free(ppx->f_in);
	if (ppx->f_out != NULL)
		free(ppx->f_out);
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
			printf("cmd freed = %s$\n", av[i]);
			free(av[i]);
			av[i] = NULL;
			printf("cmd after free = %s$\n", av[i]);
			i++;
		}
		free(av);
		av = NULL;
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
		ft_close_fds(ppx);
		waitpid(ppx->pid[i], &wstatus, 0);
		if ((ppx->cmd[i][0] != NULL && is_prefork_builtin(ppx->cmd[i]) == 0)
			|| (g_exit_status == 131 || g_exit_status == 130))
			statuscode = g_exit_status;
		if (WIFEXITED(wstatus))
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
