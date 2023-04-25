/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:56:43 by mguerga           #+#    #+#             */
/*   Updated: 2023/04/24 12:04:38 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//void	ft_parse(t_minish *minish)
//{
//	ft_token(minish);
//	ft_preced(minish);
//	ft_checkpath(minish);
//}

int	main(int ac, char *av[], char *env[])
{
	(void) av;
	if (ac != 1)
		return (1);
	ft_signals();
	(void)env;
	//minish.env = ft_copy_env(env);
	//if (minish.env == NULL)
	//	return (1);
	prompter();
	return (0);
}

void	prompter(void)
{
	t_minish	minish;

	while (1)
	{
		if (minish.line == NULL)
			exit(0);
		minish.line = readline("(ಠ.ಠ)¬ ");
		add_history(minish.line);
//		ft_parse(minish);
		free(minish.line);
	}
}
