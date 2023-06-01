/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <lzito@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:46:25 by lzito             #+#    #+#             */
/*   Updated: 2023/06/01 08:48:00 by mguerga          ###   ########.fr       */
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

int	is_prefork_builtin(char **cmd)
{
	int			i;
	const char	*builtin[] = {
		"exit", "cd", "unset", NULL,
	};

	i = 0;
	while (builtin[i] != NULL)
	{
		if (ft_strncmp(cmd[0], builtin[i], ft_strlen(builtin[i])) == 0)
			return (0);
		else if (ft_strncmp(cmd[0], "export\0", 7) == 0 && cmd[1] != NULL)
			return (0);
		i++;
	}
	return (-1);
}

int	num_of_line(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	return (i + 2);
}

char	*ft_strjoin_n_free(char *s1, char *s2)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (ptr == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	free (s1);
	return (ptr);
}
