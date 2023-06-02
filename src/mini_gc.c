/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_gc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:09:32 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/02 02:26:42 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*gc_malloc(size_t size)
{
	t_gc	*garb;

	garb = ft_calloc(1, sizeof(t_gc) + size);
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

void	*ft_gc(void *garb, int status)
{
	static t_list	*gc_list;
	void			*temp;

	if (status == ADD)
		ft_lstadd_front(&gc_list, ft_lstnew(garb));
	else if (status == EXT)
	{
		temp = gc_malloc(sizeof(garb));
		ft_memcpy(temp, garb, sizeof(garb));
		free(garb);
		return (temp);
	}
	else
		gc_lstclear(&gc_list, free);
	return (NULL);
}

void	gc_lstdelone(t_list *lst, void (*del)(void*))
{
	void	*node;
//	t_gc 	*gc;

	node = lst->content;
//	gc = (t_gc *)node;
//	printf("gc flush = %d\n", gc->flush);
//	if (gc->flush == 0)
//		return ;
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

char	*gc_substr(char const *s, unsigned int start, size_t len)
{
	void	*temp;

	temp = ft_substr(s, start, len);
	ft_gc(temp, EXT);
	gc_free(temp);
	return (temp);
}

char	*gc_strjoin(const char *s1, const char *s2)
{
	void	*temp;

	temp = ft_strjoin(s1, s2);
	ft_gc(temp, EXT);
	gc_free(temp);
	return (temp);
}
