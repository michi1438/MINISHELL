/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_gc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:09:32 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/03 17:55:04 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*gc_malloc(size_t size)
{
	void	*garb;

	garb = ft_calloc(1, size);
	ft_gc(garb, ADD);
	return (garb);
}

void	*ft_gc(void *garb, int status)
{
	static t_list	*gc_list;

	if (status == ADD)
		ft_lstadd_front(&gc_list, ft_lstnew(garb));
	else
		gc_lstclear(&gc_list, free);
	return (NULL);
}

void	gc_lstdelone(t_list *lst, void (*del)(void*))
{
	void	*node;

	node = lst->content;
	if (lst && del && node)
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

char	*gc_strjoin(char *s1, char *s2)
{
	void	*temp;

	temp = ft_strjoin(s1, s2);
	free(s1);
	return (temp);
}
