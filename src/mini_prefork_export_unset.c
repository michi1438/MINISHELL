/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_prefork_export_unset.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:51:00 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/04 19:41:12 by lzito            ###   ########.fr       */
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
	char	*var;
	char	*var_cpy;
	char	*temp;

	i = 0;
	while (cmd[j][i] && cmd[j][i] != '=')
		i++;
	if (cmd[j][i] != '=')
		return (NULL);
	var = ft_substr(cmd[j], 0, ++i);
	var_cpy = ft_strdup(var);
	i = -1;
	temp = check_env_var(minish->env, var_cpy);
	if (temp != NULL)
	//TODO MALLOC A PROTEGER !!!
		new_env = ft_calloc(num_of_line(minish->env), sizeof(char *));
	else
	//TODO MALLOC A PROTEGER !!!
		new_env = ft_calloc(num_of_line(minish->env) + 1, sizeof(char *));
	while (minish->env[++i] != NULL)
	{
		if (ft_strncmp(minish->env[i], var, ft_strlen(var)) == 0)
			new_env[i] = ft_strdup(cmd[j]);
		else
			new_env[i] = ft_strdup(minish->env[i]);
	}
	if (temp == NULL)
		new_env[i] = ft_strdup(cmd[j]);
	free(var);
	free(temp);
	return (new_env);
}

void	free_double(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		free(env[i++]);
	free (env);
}

char	**builtin_unset(char **cmd, t_minish *minish)
{
	int		j;
	int		i;
	int		e;
	char	*var;
	char	**new_env;

	//TODO MALLOC A SUIVRE ET PROTEGER !!!
	new_env = ft_calloc(new_env_size(cmd, minish), sizeof(char *));
	if (!new_env)
		return (NULL);
	e = 0;
	j = 0;
	while (minish->env[j] != NULL)
	{
		i = 0;
		while (cmd[++i] != NULL)
		{
			var = ft_strjoin(cmd[i], "=");
			if (ft_strncmp(var, minish->env[j], ft_strlen(var)) == 0 && j++)
			{
				free(var);
				break ;
			}
			free(var);
		}
		if (cmd[i] == NULL && new_env_size(cmd, minish) > 2)
			new_env[e++] = ft_strdup(minish->env[j++]);
	}
	free_double(minish->env);
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
			free (var);
		}
		j++;
	}
	return (num_of_line(minish->env) - e);
}
