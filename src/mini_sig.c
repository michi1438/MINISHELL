/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_sig.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:46:27 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/03 11:37:23 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_signals(void)
{
	struct sigaction	*act_int;
	struct sigaction	*act_quit;

	act_int = malloc(sizeof(struct sigaction));
	act_quit = malloc(sizeof(struct sigaction));
	set_act_int(act_int);
	set_act_quit(act_quit);
}

void	set_act_int(struct sigaction *act_int)
{
	sigemptyset(&act_int->sa_mask);
	act_int->sa_flags = SA_RESTART;
	act_int->sa_handler = re_prompt;
	sigaddset(&act_int->sa_mask, SIGINT);
	sigaction(SIGINT, act_int, NULL);
}

void	set_act_quit(struct sigaction *act_quit)
{
	sigemptyset(&act_quit->sa_mask);
	act_quit->sa_flags = 0;
	act_quit->sa_handler = SIG_IGN;
	sigaction(SIGQUIT, act_quit, NULL);
}

void	re_prompt(int useless)
{
	struct termios		*termi;

	termi = malloc(sizeof(struct termios));
	tcgetattr(0, termi);
	printf("%lu\n", (unsigned long)termi->c_iflag);
	printf("%lu\n", (unsigned long)termi->c_oflag);
	write(0, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)useless;
}
