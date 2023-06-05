/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_builtins_echo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 08:07:55 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/05 08:14:56 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_echo(char **cmd)
{
	int		i;
	int		flg;

	i = 1;
	flg = 0;
	while (cmd[i] != NULL)
	{
		if (ft_strncmp(cmd[i], "-n", 2) == 0 && flg == 0 && i == 1)
			echo_option(cmd, &i, &flg);
		ft_putstr_fd(cmd[i], STDOUT_FILENO);
		if (cmd[(i++) + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (flg == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	exit (0);
}

void	echo_option(char **cmd, int *i, int *flg)
{
	int	j;

	while (ft_strncmp(cmd[*i], "-n", 2) == 0)
	{
		j = 2;
		while (cmd[*i][j] == 'n')
			j++;
		if (cmd[*i][j] == '\0')
		{
			(*flg) = 1;
			(*i)++;
		}
		else
			break ;
	}
}
