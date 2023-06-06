/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:55:02 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/06 11:55:36 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	mini_lstdelone(t_list *node, void (*del)(void*))
{
	t_content	*cont;

	cont = node->content;
	if (node && del)
	{
		del(cont->str);
		del(cont);
		free(node);
	}
}

void	mini_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	temp = *lst;
	if (*lst && del)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			mini_lstdelone(*lst, del);
			*lst = temp;
		}
	}
}
