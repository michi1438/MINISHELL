/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_prefork_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:10:51 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/06 10:22:19 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_export(char **cmd, t_minish *minish)
{
	int		j;
	int		flg;
	char	**temp;

	flg = 0;
	j = 0;
	while (cmd[++j] != NULL)
	{
		if (!(ft_isalpha(cmd[j][0])))
		{
			printf("%s: not a valid identifier.\n", cmd[j]);
			g_exit_status = 1;
			flg = 1;
		}
		else
		{
			temp = new_env_maker(cmd, minish, j);
			if (temp != NULL)
			{
				free_double(minish->env);
				minish->env = temp;
			}
			g_exit_status = flg;
		}
	}
}

char	**new_env_maker(char **cmd, t_minish *minish, int j)
{
	int		i;
	char	**new_env;
	char	*temp[2];

	i = 0;
	while (cmd[j][i] && cmd[j][i] != '=')
		i++;
	if (cmd[j][i] != '=')
		return (NULL);
	new_env = alloc_env(minish, cmd[j], &i, temp);
	if (new_env != NULL)
	{
		while (minish->env[++i] != NULL)
		{
			if (ft_strncmp(minish->env[i], temp[0], ft_strlen(temp[0])) == 0)
				new_env[i] = ft_strdup(cmd[j]);
			else
				new_env[i] = ft_strdup(minish->env[i]);
		}
		if (temp[1] == NULL)
			new_env[i] = ft_strdup(cmd[j]);
	}
	free(temp[0]);
	free(temp[1]);
	return (new_env);
}

char	**alloc_env(t_minish *minish, char *cmd, int *i, char *temp[2])
{
	char	*var_cpy;

	temp[0] = ft_substr(cmd, 0, ++(*i));
	var_cpy = ft_strdup(temp[0]);
	*i = -1;
	temp[1] = check_env_var(minish->env, var_cpy);
	if (temp[1] != NULL)
	//TODO MALLOC A PROTEGER !!!
		return (ft_calloc(num_of_line(minish->env), sizeof(char *)));
	else
	//TODO MALLOC A PROTEGER !!!
		return (ft_calloc(num_of_line(minish->env) + 1, sizeof(char *)));
}
