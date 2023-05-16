/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:25:55 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/16 15:45:42 by mguerga          ###   ########.fr       */
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
		if (cont->type >= 7 || cont->type < 2)
		{
			while (cont->type >= 7 || cont->type < 2)
			{	
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
	if (i != minish->ppx.n_cmd || i == 0)
		return (-1);
	return (0);
}
