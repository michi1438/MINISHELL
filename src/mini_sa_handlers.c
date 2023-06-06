/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_sa_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:48:52 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/06 10:49:27 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	no_re_prompt_bs(int useless)
{
	write(0, "Quit", 4);
	write(0, "\n", 1);
	g_exit_status = 131;
	rl_on_new_line();
	(void)useless;
}

void	no_re_prompt(int useless)
{
	write(0, "\n", 1);
	g_exit_status = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	(void)useless;
}

void	re_prompt(int useless)
{
	write(0, "\n", 1);
	g_exit_status = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)useless;
}
