/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_prefork_builtin.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:46:16 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/23 18:59:26 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pre_fork_builtin(char **cmd, t_minish *minish)
{
	if (minish->ppx.hd_on == 1)
		return (0);
	if (ft_strncmp(cmd[0], "cd\0", 3) == 0)
	{
		if (minish->ppx.n_cmd == 1)
			builtin_cd(cmd, minish);
		return (1);
	}
	else if (ft_strncmp(cmd[0], "export\0", 3) == 0)
	{
		if (minish->ppx.n_cmd == 1)
		{
			if (cmd[1] == NULL)
				export_noarg(minish);
			else
				minish->env = builtin_export(cmd, minish);
		}
		return (1);
	}
	else
		return (0);
}

void	export_noarg(t_minish *minish)
{
	int		i;
	int		flg;
	int		j;
	
	i = 0;
	while (minish->env[i] != NULL)
	{
		j = 0;
		flg = 0;
		ft_putstr_fd("declare -x ", STDOUT_FILENO);	
		while (minish->env[i][j] != '\0')
		{
			ft_putchar_fd(minish->env[i][j], STDOUT_FILENO);	
			if (minish->env[i][j++] == '=' && flg == 0)
			{
				flg = 1;
				ft_putchar_fd('"', STDOUT_FILENO);	
			}
		}
		ft_putchar_fd('"', STDOUT_FILENO);	
		ft_putchar_fd('\n', STDOUT_FILENO);	
		i++;
	}
}
				
	
char	**builtin_export(char **cmd, t_minish *minish)
{
	char	**new_env;
	int		i;
	char	*var;

	i = 0;
	while (cmd[1][i] && cmd[1][i] != '=')
		i++;
	if (cmd[1][i] == '\0')
		return (minish->env);
	var = ft_substr(cmd[1], 0, ++i);
	i = 0;
	if (check_env_var(minish->env, var) != NULL)
		new_env = ft_calloc(num_of_line(minish->env), sizeof(char *));
	else
		new_env = ft_calloc(num_of_line(minish->env) + 1, sizeof(char *));
	while (minish->env[i] != NULL)
	{
		if (ft_strncmp(minish->env[i], var, ft_strlen(var)) == 0)
			new_env[i] = ft_strdup(cmd[1]);
		else
			new_env[i] = minish->env[i];
		i++;
	}
	if (check_env_var(minish->env, var) == NULL)
		new_env[i] = ft_strdup(cmd[1]);
	return (new_env);
}

int	num_of_line(char **env)
{
	int	i;
	
	i = 0;
	while (env[i] != NULL)
		i++;
	return (i + 2);
}

void	builtin_cd(char **cmd, t_minish *minish)
{
	if (cmd[1] != NULL)
	{
		chdir(cmd[1]);
		if (chdir(cmd[1]) == -1)
			perror(cmd[1]);
	}
	else 
		chdir(check_env_var(minish->env, "HOME="));
}
