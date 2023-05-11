/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <lzito@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:46:25 by lzito             #+#    #+#             */
/*   Updated: 2023/05/11 19:07:41 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_copy_env(char *env[])
{
	int		i;
	char	**cpy_env;

	i = 0;
	while (env[i])
		i++;
	cpy_env = malloc((i + 2) * sizeof(char *));
	if (cpy_env == NULL)
		return (NULL);
	i = 0;
	while (env[i])
	{
		cpy_env[i] = ft_strdup(env[i]);
		i++;
	}
	cpy_env[i] = NULL;
	return (cpy_env);
}

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
