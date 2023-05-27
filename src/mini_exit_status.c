/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 11:57:57 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/27 11:58:44 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_exit_stat(char *fullpath, t_pipex *ppx, char *cmd)
{
	if (access(fullpath, F_OK) == -1 && ft_strncmp(cmd, "exit", 5) != 0)
		ppx->last_exit_status = 127;
	else if (access(fullpath, X_OK) == -1 && ft_strncmp(cmd, "exit", 5) != 0)
		ppx->last_exit_status = 126;
}

