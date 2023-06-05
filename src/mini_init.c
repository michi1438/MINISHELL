/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:55:39 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/05 13:56:03 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_initmain(t_minish *minish, char **env)
{
	ft_signals_n_attr(SET);
	g_exit_status = 0;
	minish->prev_line = NULL;
	minish->env = ft_copy_env(env);
	if (minish->env == NULL)
		return (1);
	return (0);
}

int	init_minish(t_minish *minish)
{
	minish->lst_line = NULL;
	ft_signals_n_attr(RESET);
	minish->ppx.n_cmd = 1;
	return (0);
}
