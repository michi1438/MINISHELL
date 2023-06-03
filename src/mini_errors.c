/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:25:55 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/03 21:48:34 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_err_handling(t_minish *minish)
{
	int			i;
	t_list		*lst;
	t_content	*cont;

	i = 0;
	lst = minish->lst_line;
	while (lst != NULL)
	{
		cont = lst->content;
		if (cont->type != SPCE && cont->type != PIPE)
		{
			while (cont->type != PIPE)
			{	
				if (cont->type >= APP_OUT && cont->type <= REDIR_IN
					&& cont->str == NULL)
					i--;
				lst = lst->next;
				if (lst == NULL)
					break ;
				cont = lst->content;
			}
			i++;
		}
		if (lst != NULL)
			lst = lst->next;
	}
	mini_lstclear(&minish->lst_line, free);
	if (i != minish->ppx.n_cmd)
		return (ft_pre_free(minish));
	return (0);
}
