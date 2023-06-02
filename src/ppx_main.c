/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:29:12 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/02 00:04:50 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_looppid(t_pipex *ppx, t_minish *minish, int idx)
{
	ft_signals_n_attr(NO_REPROMPT);
	ppx->pid[idx] = fork();
	if (ppx->pid[idx] < 0)
		exit(1);
	if (ppx->pid[idx] == 0)
	{
		if (ppx->n_cmd == 1)
			ft_redir_only_cmd(ppx, idx);
		else if (idx == 0)
			ft_redir_first_cmd(ppx, idx);
		else if (idx == ppx->n_cmd - 1)
			ft_redir_last_cmd(ppx, idx);
		else
			ft_redir_mid_cmd(ppx, idx);
		ft_close_fds(ppx);
		ft_signals_n_attr(UNSET);
		check_for_builtin(ppx->cmd[idx], minish, idx);
		execve(ppx->path[idx], ppx->cmd[idx], minish->env);
		perror(ppx->cmd[idx][0]);
		if (errno == ENOENT || ppx->cmd[idx][0] == NULL)
			exit(127);
		exit(126);
	}
	return ;
}

int	ft_feedppx(t_pipex *ppx, char **av, char **env)
{
	int	i;

	i = 0;
	while (i < ppx->n_cmd)
	{
		//TODO create a function for this HD part
		if (ppx->hd_on[i] == 1)
		{
			ppx->fd_hd[i] = ft_calloc(2, sizeof(int));
			if (ppx->fd_hd[i] == NULL)
				return (ft_error(av[0], -1));
			if (pipe(ppx->fd_hd[i]) == -1)
				ft_error(av[0], -3);
			if (ft_heredoc(ppx, i) == -1)
				return (ft_error(av[0], -1));
		}
		ppx->cmd[i] = ft_mod_split(av[i], ' ');
//		free(av[i]);
		if (ppx->cmd[i] == NULL)
			return (ft_error(av[0], -1));
		ppx->path[i] = ft_checkpath(env, ppx->cmd[i][0]);
		ppx->fd[i] = ft_calloc(2, sizeof(int));
		if (ppx->fd[i] == NULL)
			return (ft_error(av[0], -1));
		if (pipe(ppx->fd[i]) == -1)
			return (ft_error(av[0], -3));
		i++;
	}
//	free(av);
	return (0);
}

int	ft_initppx_io(t_pipex *ppx, t_minish *minish)
{
	int	i;

	(void) minish;
	i = 0;
	while (i < ppx->n_cmd)
	{
		if (ppx->filein[i] == NULL)
			ppx->f_in[i] = 0;
		if (ppx->fileout[i] == NULL)
			ppx->f_out[i] = 1;
		if (ppx->fileout[i] != NULL)
		{
			if (ppx->app_on[i] == 0)
				ppx->f_out[i] = open(ppx->fileout[i], O_CREAT | O_WRONLY | O_TRUNC, 00644);
			else
				ppx->f_out[i] = open(ppx->fileout[i], O_CREAT | O_APPEND | O_WRONLY, 00644);
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

int	ft_initppx(t_pipex *ppx, t_minish *minish)
{
	ppx->pid = ft_calloc(ppx->n_cmd, sizeof(int));
	if (ppx->pid == NULL)
		return (ft_error(minish->cmds[0], -1));
	ppx->cmd = ft_calloc(ppx->n_cmd, sizeof(char **));
	if (ppx->cmd == NULL)
		return (ft_error(minish->cmds[0], -1));
	ppx->path = ft_calloc(ppx->n_cmd, sizeof(char *));
	if (ppx->path == NULL)
		return (ft_error(minish->cmds[0], -1));
	ppx->fd = ft_calloc(ppx->n_cmd, sizeof(int *));
	if (ppx->fd == NULL)
		return (ft_error(minish->cmds[0], -1));
	ppx->fd_hd = ft_calloc(ppx->n_cmd, sizeof(int *));
	if (ppx->fd_hd == NULL)
		return (ft_error(minish->cmds[0], -1));
	ppx->f_in = ft_calloc(ppx->n_cmd, sizeof(int));
	if (ppx->f_in == NULL)
		return (ft_error(minish->cmds[0], -1));
	ppx->f_out = ft_calloc(ppx->n_cmd, sizeof(int));
	if (ppx->f_out == NULL)
		return (ft_error(minish->cmds[0], -1));
	if (ft_initppx_io(ppx, minish) == -1)
		return (-1);
	if (ft_feedppx(ppx, minish->cmds, minish->env) == -1)
		return (-1);
	return (0);
}

int	main_pipe(t_minish *minish, t_pipex *ppx)
{
	int		i;
	int		initstatus;

	i = 0;
	initstatus = ft_initppx(ppx, minish);
	if (initstatus < 0)
	{
		if (initstatus == -1)
			ft_freeall(ppx);
		return (1);
	}
	while (i < ppx->n_cmd)
	{
		if (pre_fork_builtin(ppx->cmd[i], minish) == 0)
			ft_looppid(ppx, minish, i);
		i++;
	}
	return (ft_waitnclose(ppx));
}
