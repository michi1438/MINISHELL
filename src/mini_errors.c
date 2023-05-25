/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:25:55 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/25 16:18:45 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_err_check_hd(t_minish *minish, t_content *cont, int i)
{
	i++;
	if (cont->str != NULL && minish->ppx.n_cmd == i - 1)
		minish->ppx.n_cmd++;
	return (i);
}

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
		if (cont->type > SPCE || cont->type < PIPE)
		{
//			printf("cont = %s$\n", cont->str);
			while (cont->type >= SPCE || cont->type < PIPE)
			{	
				lst = lst->next;
				if (lst == NULL)
					break ;
				cont = lst->content;
			}
			i = ft_err_check_hd(minish, cont, i);
		}
		if (lst != NULL)
			lst = lst->next;
	}
//	printf("i = %d n_cmd = %d\n", i, minish->ppx.n_cmd);
	if (i != minish->ppx.n_cmd || (i == 0 && minish->ppx.hd_on == 0))
		return (-1);
	return (0);
}
