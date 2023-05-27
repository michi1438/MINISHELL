/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 11:57:57 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/27 15:34:04 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_exit_stat(char *fullpath, t_pipex *ppx, char *cmd)
{
	if (is_builtin(cmd) == -1)
	{
		if (access(fullpath, F_OK) == -1)
			ppx->last_exit_status = 127;
		else if (access(fullpath, X_OK) == -1)
			ppx->last_exit_status = 126;
	}
}

int	is_builtin(char *cmd)
{
	int			i;
	const char	*builtin[] = {
		"echo", "exit", "cd", "pwd", "export", "env", NULL,
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
