/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:26:58 by mguerga           #+#    #+#             */
/*   Updated: 2023/04/20 20:47:20 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char *av[], char *env[])
{
	char	*line;

	(void)ac;
	(void)av;
	(void)env;
	ft_signals();
	while (1)
	{
		line = readline(">>> ");
		if (line == NULL)
			ft_gc(NULL, DEL);
	}
	return (0);
}
