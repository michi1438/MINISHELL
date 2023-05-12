/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:00:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/12 21:35:10 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_for_builtin(char **cmd)
{
	if (ft_strncmp(cmd[0], "echo\0", 5) == 0)
		builtin_echo(cmd);
}

void	builtin_echo(char **cmd)
{
	int		i;
	int		flg;

	i = 1;
	flg = 0;
	if (ft_strncmp(cmd[i], "-n", 2) == 0)
	{
		i++;
		flg = 1;
	}
	while (cmd[i] != NULL)
	{
		ft_putstr_fd(cmd[i], STDOUT_FILENO);
		if (cmd[(i++) + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (flg == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	exit (0);
}
