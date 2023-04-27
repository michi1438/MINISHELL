/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_gc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:09:32 by mguerga           #+#    #+#             */
/*   Updated: 2023/04/25 16:22:18 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*gc_malloc(size_t size, int status)
{
	void	*ptr;

	ptr = malloc(size);
	ft_gc(ptr, status);
	return (ptr);
}

void	ft_gc(void *ptr, int status)
{
	static t_list	*gc_list;

	if (status == ADD)
		ft_lstadd_front(&gc_list, ptr);
	else
	{
		ft_lstclear(&gc_list, free);
		exit(0);
	}
}
