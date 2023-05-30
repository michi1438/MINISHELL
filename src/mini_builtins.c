/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:00:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/30 13:18:29 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

void	check_for_builtin(char **cmd, t_minish *minish)
{
	if (cmd[0] == NULL)
		return ;
	if (ft_strncmp(cmd[0], "echo\0", 5) == 0)
		builtin_echo(cmd, minish);
	else if (ft_strncmp(cmd[0], "pwd\0", 4) == 0)
		builtin_pwd();
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

int	is_prefork_builtin(char *cmd)
{
	int			i;
	const char	*builtin[] = {
		"exit", "export", "env", "unset",  NULL,
	};

	i = 0;
	while (builtin[i] != NULL)
	{
		if (ft_strncmp(cmd, builtin[i], ft_strlen(builtin[i])) == 0)
			return (0);
		i++;
	}
	return (-1);
}
