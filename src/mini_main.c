/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:56:41 by mguerga           #+#    #+#             */
/*   Updated: 2023/04/20 15:15:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av)
{
	(void)av;
	bs_func();
	if (ac == 1)
	{
		write(1, "\n", 1);
		return (0);
	}
	return (0);
}

void	bs_func(void)
{
	char	*test1 = NULL;
	char	*test2 = NULL;

	test1 = malloc(sizeof(char) * 10);
	add_to_gc(test1, ADD_NODE);
	test2 = gc_malloc(sizeof(char) * 10, ADD_NODE);
	printf("   %p\n", test1);
	printf("   %p\n", test2);
}
