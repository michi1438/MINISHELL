/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:00:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/22 13:26:44 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_for_builtin(char **cmd)
{
	if (ft_strncmp(cmd[0], "echo\0", 5) == 0)
		builtin_echo(cmd);
	else if (ft_strncmp(cmd[0], "pwd\0", 4) == 0)
		builtin_pwd();
}

int	pre_fork_builtin(char **cmd, t_minish *minish)
{
	if (ft_strncmp(cmd[0], "cd\0", 3) == 0)
	{
		if (minish->ppx.n_cmd == 1)
			builtin_cd(cmd, minish);
		return (1);
	}
	else
		return (0);
}
	
void	builtin_cd(char **cmd, t_minish *minish)
{
	if (cmd[1] != NULL)
	{
		chdir(cmd[1]);
		if (chdir(cmd[1]) == -1)
			perror(cmd[1]);
	}
	else 
		chdir(check_env_var(minish->env, "HOME="));
}

void	builtin_pwd(void)
{
	ft_putstr_fd(getcwd(NULL, 0), STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	exit (0);
}

void	builtin_echo(char **cmd)
{
	int		i;
	int		flg;

	i = 1;
	flg = 0;
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
