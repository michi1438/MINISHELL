/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:00:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/12 16:54:13 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_for_builtin(char **cmd)
{
	if (ft_strncmp(cmd[0], "echo", 4) == 0)
		builtin_echo(cmd);
}

void	builtin_echo(char **cmd)
{
	int		i;

	i = 1;
	while (cmd[i] != NULL)
	{
		ft_putstr_fd(cmd[i], STDOUT_FILENO);
		if (cmd[(i++) + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	exit (0);
}
