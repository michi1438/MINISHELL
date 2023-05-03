/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:29:12 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/03 21:52:26 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_looppid(t_pipex *ppx, char **env, int idx)
{
	ppx->pid[idx] = fork();
	if (ppx->pid[idx] < 0)
		exit(1);
	if (ppx->pid[idx] == 0)
	{
		if (ppx->n_cmd == 1)
			ft_dup(ppx->f_in, ppx->f_out);
		else if (idx == 0)
		{
			if (ppx->hd_on == 0)
				ft_dup(ppx->f_in, ppx->fd[idx][1]);
			else
				ft_dup(ppx->fd_hd[0], ppx->fd[idx][1]);
		}
		else if (idx == ppx->n_cmd - 1)
			ft_dup(ppx->fd[idx - 1][0], ppx->f_out);
		else
			ft_dup(ppx->fd[idx - 1][0], ppx->fd[idx][1]);
		ft_close_fds(ppx);
		execve(ppx->path[idx], ppx->cmd[idx], env);
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
//	if (ppx->hd_on == 1)
//	{
//		if (ft_heredoc(ppx) == -1)
//			return (ft_error(av[0], -1));
//	}
	while (i < ppx->n_cmd)
	{
		ppx->cmd[i] = ft_split(av[i], ' ');
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
	return (0);
}

int	ft_initppx(t_pipex *ppx, t_minish *minish)
{
//	ppx->f_out = open(fileout, O_CREAT | O_WRONLY | O_TRUNC, 00644);
//	if (ppx->f_out == -1)
//		return (ft_error(av[ac - 1], -2));
	//ppx->n_cmd = minish->n_pipe + 1;
//	if (ppx->hd_on == 0)
//	{
//		ppx->f_in = open(filein, O_RDONLY);
//		if (ppx->f_in == -1)
//			return (ft_error(av[1], -2));
//	}
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
	if (ft_feedppx(ppx, minish->cmds, minish->env) == -1)
		return (-1);
	return (0);
}

int	main_pipe(t_minish *minish, t_pipex *ppx)
{
	int		i;
	int		initstatus;

	i = 0;
//	ft_checkheredoc(argv, &ppx);
	initstatus = ft_initppx(ppx, minish);
	if (initstatus < 0)
	{
		if (initstatus == -1)
			ft_freeall(ppx);
		return (1);
	}
	while (i < ppx->n_cmd)
	{
		ft_looppid(ppx, minish->env, i);
		i++;
	}
	return (ft_waitnclose(ppx));
}
