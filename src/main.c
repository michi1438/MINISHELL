/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:56:41 by mguerga           #+#    #+#             */
/*   Updated: 2023/04/19 16:18:39 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

int	main(int ac, char **av)
{
	(void)av;
	if (ac == 1)
	{
		write(1, "\n", 1);
		return (0);
	}
}
