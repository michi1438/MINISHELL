/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:56:41 by mguerga           #+#    #+#             */
/*   Updated: 2023/04/20 12:00:49 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main_minish(int ac, char *av[], char* env)
{
	(void) ac;
	(void) av;
	(void) env;
	char	*line;

	while (1)
	{
		line = returnline("MINISH >>>");
		if (line == NULL)
			printf("%s\n", line);
	}
//	if (ac == 1)
//	{
//		write(1, "\n", 1);
//		return (0);
//	}
	return (0);
}
