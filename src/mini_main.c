/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:56:41 by mguerga           #+#    #+#             */
/*   Updated: 2023/04/20 15:15:19 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char *av[], char* env[])
{
	(void) ac;
	(void) av;
	(void) env;
	char	*line;

	while (1)
	{
		line = readline(">>> ");
		if (ft_strncmp(line, "exit", ft_strlen(line)) == 0)
			return (0);
	}
	return (0);
}
