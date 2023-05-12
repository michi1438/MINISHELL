/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:00:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/12 11:38:02 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_for_builtin(t_minish *minish)
{
	int			i;
	char		*cmd;

	i = 0;
	while (minish->cmds[i] != NULL)
	{
		cmd = minish->cmds[i];
		if (ft_strncmp(cmd, "echo", 4) == 0)
		{
			builtin_echo(&cmd[5]);
			return (0);
		}
		i++;
	}
	return (1);
}

void	builtin_echo(char *cmd)
{
	if (ft_strncmp(cmd, "-n", 2) == 0)
		ft_putstr_fd(&cmd[3], 1);
	else
	{
		ft_putstr_fd(cmd, 1);
		ft_putchar_fd('\n', 1);
	}
}
