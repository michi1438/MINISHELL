/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:26:58 by mguerga           #+#    #+#             */
/*   Updated: 2023/04/20 15:28:41 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char *av[], char *env[])
{
	char	*line;

	(void)ac;
	(void)av;
	(void)env;
	while (1)
	{
		line = readline(">>> ");
		if (ft_strncmp(line, "exit", ft_strlen(line)) == 0)
			return (0);
	}
	return (0);
}