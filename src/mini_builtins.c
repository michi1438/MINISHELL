/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:00:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/31 14:22:39 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_for_builtin(char **cmd, t_minish *minish, int i)
{
	if (cmd[0] == NULL)
	{
		if (minish->ppx.limiter[i] != NULL
			|| minish->ppx.filein[i] != NULL
			|| minish->ppx.fileout[i] != NULL)
			exit (0);
		return ;
	}
	if (ft_strncmp(cmd[0], "echo\0", 5) == 0)
		builtin_echo(cmd, minish);
	else if (ft_strncmp(cmd[0], "pwd\0", 4) == 0)
		builtin_pwd();
	else if (ft_strncmp(cmd[0], "export\0", 7) == 0 && cmd[1] == NULL)
		export_noarg(minish);
}

void	export_noarg(t_minish *minish)
{
	int		i;
	int		flg;
	int		j;

	i = 0;
	while (minish->env[i] != NULL)
	{
		j = 0;
		flg = 0;
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		while (minish->env[i][j] != '\0')
		{
			ft_putchar_fd(minish->env[i][j], STDOUT_FILENO);
			if (minish->env[i][j++] == '=' && flg == 0)
			{
				flg = 1;
				ft_putchar_fd('"', STDOUT_FILENO);
			}
		}
		ft_putchar_fd('"', STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	exit (0);
}

void	builtin_pwd(void)
{
	ft_putstr_fd(getcwd(NULL, 0), STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	exit (0);
}

void	builtin_echo(char **cmd, t_minish *minish)
{
	int		i;
	int		flg;

	i = 1;
	flg = 0;
	(void)minish;
	while (cmd[i] != NULL)
	{
		if (ft_strncmp(cmd[i], "-n", 2) == 0)
		{
			i++;
			flg = 1;
		}
		else
		{
			ft_putstr_fd(cmd[i], STDOUT_FILENO);
			if (cmd[(i++) + 1] != NULL)
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
	}
	if (flg == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	exit (0);
}
