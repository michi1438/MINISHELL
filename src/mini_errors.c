/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:25:55 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/05 09:13:09 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_err_handling(t_minish *minish)
{
	int			i;
	t_list		*lst;

	i = 0;
	lst = minish->lst_line;
	while (lst != NULL)
		lst = counting_cmd(&i, lst);
	mini_lstclear(&minish->lst_line, free);
	if (i != minish->ppx.n_cmd)
		return (ft_pre_free(minish));
	return (0);
}

t_list	*counting_cmd(int *i, t_list *lst)
{
	t_content	*cont;

	cont = lst->content;
	if (cont->type != SPCE && cont->type != PIPE)
	{
		while (cont->type != PIPE)
		{	
			if (cont->type >= APP_OUT && cont->type <= REDIR_IN
				&& cont->str == NULL)
				(*i)--;
			lst = lst->next;
			if (lst == NULL)
				break ;
			cont = lst->content;
		}
		(*i)++;
	}
	if (lst != NULL)
		lst = lst->next;
	return (lst);
}
