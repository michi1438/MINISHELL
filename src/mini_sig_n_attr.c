/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_sig_n_attr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:42:02 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/06 10:49:21 by mguerga          ###   ########.fr       */
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
		tcgetattr(STDIN_FILENO, &termi);
		oldtermi = termi;
		termi.c_lflag = ECHO;
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &termi);
	}
	else
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &oldtermi);
	set_act_quit(&act_quit, toggle);
	set_act_int(&act_int, toggle);
}

void	set_act_int(struct sigaction *act_int, int toggle)
{
	static struct sigaction	old_int;

	if (toggle == SET)
		sigaction(SIGINT, NULL, &old_int);
	else if (toggle == RESET)
	{
		sigemptyset(&act_int->sa_mask);
		act_int->sa_flags = SA_RESTART;
		act_int->sa_handler = re_prompt;
		sigaddset(&act_int->sa_mask, SIGINT);
		sigaction(SIGINT, act_int, NULL);
	}
	else if (toggle == UNSET)
		sigaction(SIGINT, &old_int, NULL);
	else
	{
		sigemptyset(&act_int->sa_mask);
		act_int->sa_handler = no_re_prompt;
		sigaddset(&act_int->sa_mask, SIGINT);
		sigaction(SIGINT, act_int, NULL);
	}
}

void	set_act_quit(struct sigaction *act_quit, int toggle)
{
	static struct sigaction	old_quit;

	if (toggle == SET)
		sigaction(SIGQUIT, NULL, &old_quit);
	else if (toggle == UNSET)
		sigaction(SIGQUIT, &old_quit, NULL);
	else if (toggle == NO_REPROMPT)
	{
		sigemptyset(&act_quit->sa_mask);
		act_quit->sa_flags = 0;
		act_quit->sa_handler = no_re_prompt_bs;
		sigaction(SIGQUIT, act_quit, NULL);
	}
	else
	{	
		sigemptyset(&act_quit->sa_mask);
		act_quit->sa_flags = 0;
		act_quit->sa_handler = SIG_IGN;
		sigaction(SIGQUIT, act_quit, NULL);
	}
}
