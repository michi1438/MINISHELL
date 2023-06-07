/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:29:12 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/07 17:34:27 by mguerga          ###   ########.fr       */
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
	int	ret;

	i = 0;
	while (i < ppx->n_cmd)
	{
		if (ppx->hd_on[i] == 1)
		{
			ppx->fd_hd[i] = w_ft_calloc_prot(2, sizeof(int));
			if (pipe(ppx->fd_hd[i]) == -1)
				ft_error(av[0], -3);
			if (ft_heredoc(ppx, i) == -1)
				return (ft_error(av[0], -1));
		}
		ppx->cmd[i] = ft_mod_split(av[i], ' ');
		if (ppx->cmd[i] == NULL)
			return (ft_error(av[0], -1));
		ret = feed_err(av, ppx, env, &i);
		if (ret != 0)
			return (ret);
	}
	return (0);
}

int	feed_err(char **av, t_pipex *ppx, char **env, int *i)
{
	free(av[*i]);
	ppx->path[*i] = ft_checkpath(env, ppx->cmd[*i][0]);
	ppx->fd[*i] = w_ft_calloc_prot(2, sizeof(int));
	if (pipe(ppx->fd[*i]) == -1)
		return (ft_error(av[0], -3));
	(*i)++;
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
