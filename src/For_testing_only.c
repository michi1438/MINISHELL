/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   For_testing_only.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:03:25 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/07 17:18:30 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_lst_line(t_minish minish)
{
	t_list		*lst;
	t_content	*cont;

	lst = minish.lst_line;
	while (lst != NULL)
	{
		cont = lst->content;
		printf("%s\n", cont->str);
		printf("%d\n", cont->type);
		lst = lst->next;
	}
}
