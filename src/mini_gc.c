/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:09:32 by mguerga           #+#    #+#             */
/*   Updated: 2023/04/20 15:15:35 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*gc_malloc(size_t size, int status)
{
	void	*ptr;

	ptr = malloc(size);
	add_to_gc(ptr, status);
	return (ptr);
}

void	add_to_gc(void *ptr, int status)
{
	static t_list	*gc_list;

	if (status == ADD_NODE)
		ft_lstadd_front(&gc_list, ptr);
	else
	{
		ft_lstclear(&gc_list, free);
		exit(0);
	}
}
