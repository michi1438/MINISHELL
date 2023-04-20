/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:56:43 by mguerga           #+#    #+#             */
/*   Updated: 2023/04/20 21:10:56 by lzito            ###   ########.fr       */
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
	t_minish	minish;

	(void) av;
	ft_signals();
	if (ac != 1)
		return (1);
	minish.env = ft_copy_env(env);
	if (minish.env == NULL)
		return (1);
	while (1)
	{
		minish.line = readline("(ಠ.ಠ)¬ ");
		if (minish.line == NULL)
			return (0);
		add_history(minish.line);
//		ft_parse(&minish);
		free(minish.line);
	}
	return (0);
}
