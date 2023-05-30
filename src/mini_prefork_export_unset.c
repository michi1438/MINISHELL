/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_prefork_export_unset.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:51:00 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/30 19:33:22 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_export(char **cmd, t_minish *minish)
{
	int		j;
	int		flg;

	flg = 0;
	j = 1;
	while (cmd[j] != NULL)
	{
		if (ft_isdigit(cmd[j][0]))
		{
			printf("%s: not a valid identifier.\n", cmd[j]);	
			minish->ppx.exit_status = 1;	
			flg = 1;
		}
		else
		{
			minish->env = new_env_maker(cmd, minish, j);
			if (flg == 0)
				minish->ppx.exit_status = 0;
		}
		j++;
	}
}

char	**new_env_maker(char **cmd, t_minish *minish, int j)
{
	int		i;
	char	**new_env;
	char	*var;

	i = 0;
	while (cmd[j][i] && cmd[j][i] != '=')
		i++;
	var = ft_substr(cmd[j], 0, ++i);
	i = 0;
	if (check_env_var(minish->env, var) != NULL)
		new_env = ft_calloc(num_of_line(minish->env), sizeof(char *));
	else
		new_env = ft_calloc(num_of_line(minish->env) + 1, sizeof(char *));
	while (minish->env[i] != NULL)
	{
		if (ft_strncmp(minish->env[i], var, ft_strlen(var)) == 0)
			new_env[i] = ft_strdup(cmd[j]);
		else
			new_env[i] = minish->env[i];
		i++;
	}
	if (check_env_var(minish->env, var) == NULL)
		new_env[i] = ft_strdup(cmd[j]);
	return (new_env);
}

char	**builtin_unset(char **cmd, t_minish *minish)
{
	int		j;
	int		i;
	int		e;
	char	*var;
	char	**new_env;

	new_env = ft_calloc(new_env_size(cmd, minish), sizeof(char *));
	e = 0;
	j = 0;
	while (minish->env[j] != NULL)
	{
		i = 0;
		while (cmd[++i] != NULL)
		{
			var = ft_strjoin(cmd[i], "=");
			if (ft_strncmp(var, minish->env[j], ft_strlen(var)) == 0)
			{
				j++;
				break ;
			}
		}
		if (cmd[i] == NULL)
			new_env[e++] = ft_strdup(minish->env[j++]);
	}
	return (new_env);
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
		}
		j++;
	}
	return (num_of_line(minish->env) - e);
}
