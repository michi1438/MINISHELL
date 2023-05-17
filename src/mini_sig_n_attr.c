/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_sig_n_attr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:42:02 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/17 21:58:24 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_signals_n_attr(int toggle)
{
	struct sigaction		act_int;
	struct sigaction		act_quit;
	struct termios			termi;
	static struct termios	oldtermi;

	if (toggle == SET)
	{
		tcgetattr(0, &termi);
		oldtermi = termi;
		termi.c_lflag = ECHO;
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &termi);
		set_act_int(&act_int, toggle);
		set_act_quit(&act_quit, toggle);
	}
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &oldtermi);
}

void	set_act_int(struct sigaction *act_int, int toggle)
{
	static struct sigaction	old_int;

	if (toggle == SET)
	{	
		sigemptyset(&act_int->sa_mask);
		act_int->sa_flags = SA_RESTART;
		act_int->sa_handler = re_prompt;
		sigaddset(&act_int->sa_mask, SIGINT);
		sigaction(SIGINT, act_int, &old_int);
	}
	else
	{
		sigemptyset(&act_int->sa_mask);
		sigaction(SIGQUIT, &old_int, NULL);
	}
}

void	set_act_quit(struct sigaction *act_quit, int toggle)
{
	static struct sigaction	old_quit;

	if (toggle == SET)
	{	
		sigemptyset(&act_quit->sa_mask);
		act_quit->sa_flags = 0;
		act_quit->sa_handler = SIG_IGN;
		sigaction(SIGQUIT, act_quit, &old_quit);
		printf("%p\n", &old_quit);
		printf("%p\n", &act_quit);
	}
	else
	{
		sigemptyset(&act_quit->sa_mask);
		sigaction(SIGQUIT, &old_quit, NULL);
	}
}

void	re_prompt(int useless)
{
	write(0, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)useless;
}
