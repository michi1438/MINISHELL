/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:25:55 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/31 00:20:16 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

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
		printf("cont = %s$\n", cont->str);
//		printf("type = %d$\n", cont->type);
		if (cont->type > SPCE || cont->type < PIPE)
		{
			while (cont->type >= SPCE || cont->type < PIPE)
			{	
				lst = lst->next;
				if (lst == NULL)
					break ;
				cont = lst->content;
			}
			i++;
		}
		if (cont->type >= APP_OUT && cont->type <= REDIR_IN
			&& cont->str != NULL)
			i++;
		if (lst != NULL)
			lst = lst->next;
	}
	printf("i = %d n_cmd = %d\n", i, minish->ppx.n_cmd);
	if (i != minish->ppx.n_cmd)
		return (-1);
	return (0);
}
