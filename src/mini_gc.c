/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_gc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:09:32 by mguerga           #+#    #+#             */
/*   Updated: 2023/04/30 17:08:14 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*gc_malloc(size_t size)
{
	t_gc	*garb;

	garb = malloc(sizeof(t_gc) + size);
	garb->flush = 0;
	ft_gc(garb, ADD);
	return (garb + sizeof(t_gc));
}

void	gc_free(void *ptr)
{
	t_gc	*gc;

	gc = ptr - sizeof(t_gc);
	gc->flush = 1;
}

void	ft_gc(void *garb, int status)
{
	static t_list	*gc_list;

	if (status == ADD)
		ft_lstadd_front(&gc_list, ft_lstnew(garb));
	else
		gc_lstclear(&gc_list, free);
}

void	gc_lstdelone(t_list *lst, void (*del)(void*))
{
	t_gc	*node;

	node = lst->content;
	if (lst && del)
	{
		del(node);
		free(lst);
	}
}

void	gc_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	temp = *lst;
	if (*lst && del)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			gc_lstdelone(*lst, del);
			*lst = temp;
		}
	}
}
