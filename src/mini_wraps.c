/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_wraps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:22:33 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/07 15:52:31 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*w_strjoin_rm_arg1(char *s1, char *s2)
{
	void	*temp;

	temp = ft_strjoin(s1, s2);
	free(s1);
	return (temp);
}

char	*w_itoa_rm(char *var)
{
	char	*temp;

	temp = var;
	var = ft_itoa(g_exit_status);
	free(temp);
	return (var);
}

void	*w_malloc_protect(size_t size)
{
	void	*node;

	node = malloc(size);
	if (node == NULL)
	{
		printf("Memory allocation failed !!\n");
		exit(10);
	}
	return (node);
}

void	*w_ft_calloc_prot(int nmemb, size_t size)
{
	void	*node;

	node = ft_calloc(nmemb, size);
	if (node == NULL)
	{
		printf("Memory allocation failed !!\n");
		exit(10);
	}
	return (node);
}
