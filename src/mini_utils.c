/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <lzito@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:46:25 by lzito             #+#    #+#             */
/*   Updated: 2023/05/02 13:50:08 by lzito            ###   ########.fr       */
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
	cpy_env = gc_malloc(i * sizeof(char *));
//	cpy_env = malloc(i * sizeof(char *));
	if (cpy_env == NULL)
		return (NULL);
	i = 0;
	while (env[i])
	{
		cpy_env[i] = ft_strdup(env[i]);
		ft_gc(cpy_env[i], ADD);
		printf("%s\n", cpy_env[i]);
		i++;
	}
	return (cpy_env);
}
