/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_prefork_unset.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:11:26 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/06 10:12:55 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**builtin_unset(char **cmd, t_minish *minish)
{
	int		j;
	int		i;
	int		e;
	char	**new_env;

	//TODO MALLOC A SUIVRE ET PROTEGER !!!
	new_env = ft_calloc(new_env_size(cmd, minish), sizeof(char *));
	if (!new_env)
		return (NULL);
	e = 0;
	j = 0;
	while (minish->env[j] != NULL)
	{
		i = testing_var(minish, cmd, &j);
		if (cmd[i] == NULL && new_env_size(cmd, minish) > 2)
			new_env[e++] = ft_strdup(minish->env[j++]);
	}
	free_double(minish->env);
	return (new_env);
}

int	testing_var(t_minish *minish, char **cmd, int *j)
{
	char	*var;
	int		i;

	i = 0;
	while (cmd[++i] != NULL)
	{
		var = ft_strjoin(cmd[i], "=");
		if (ft_strncmp(var, minish->env[*j], ft_strlen(var)) == 0 && (*j)++)
		{
			free(var);
			return (i);
		}
		free(var);
	}
	return (i);
}

int	new_env_size(char **cmd, t_minish *minish)
{
	int		j;
	int		i;
	int		e;
	char	*var;

	j = 1;
	e = 0;
	while (cmd[j] != NULL)
	{
		i = 0;
		while (minish->env[i] != NULL)
		{
			var = ft_strjoin(cmd[j], "=");
			if (ft_strncmp(var, minish->env[i++], ft_strlen(var)) == 0)
				e++;
			free (var);
		}
		j++;
	}
	return (num_of_line(minish->env) - e);
}
