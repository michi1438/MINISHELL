/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:00:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/23 11:38:18 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_for_builtin(char **cmd)
{
	if (ft_strncmp(cmd[0], "echo\0", 5) == 0)
		builtin_echo(cmd);
	else if (ft_strncmp(cmd[0], "pwd\0", 4) == 0)
		builtin_pwd();
}

int	pre_fork_builtin(char **cmd, t_minish *minish)
{
	if (minish->ppx.n_cmd == 1)
	{
		if (ft_strncmp(cmd[0], "cd\0", 3) == 0)
		{
			builtin_cd(cmd, minish);
			return (1);
		}
		else if (ft_strncmp(cmd[0], "export\0", 3) == 0)
		{
			minish->env = builtin_export(cmd, minish);
			return (1);
		}
		else
			return (0);
	}
	else
		return (0);
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
	i++;
	var = ft_substr(cmd[1], 0, i);
	if (check_env_var(minish->env, var) != NULL)
		new_env = ft_calloc(num_of_line(minish->env), sizeof(char *));
	else
		new_env = ft_calloc(num_of_line(minish->env) + 1, sizeof(char *));
	i = 0;
	while (minish->env[i] != NULL)
	{
		if (ft_strncmp(minish->env[i], var, ft_strlen(var)) == 0)
			new_env[i] = ft_strdup(cmd[1]);
		else
			new_env[i] = minish->env[i];
		i++;
	}
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

void	builtin_pwd(void)
{
	ft_putstr_fd(getcwd(NULL, 0), STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	exit (0);
}

void	builtin_echo(char **cmd)
{
	int		i;
	int		flg;

	i = 1;
	flg = 0;
	while (cmd[i] != NULL)
	{
		if (ft_strncmp(cmd[i], "-n", 2) == 0)
		{
			i++;
			flg = 1;
		}
		else
		{
			ft_putstr_fd(cmd[i], STDOUT_FILENO);
			if (cmd[(i++) + 1] != NULL)
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
	}
	if (flg == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	exit (0);
}
