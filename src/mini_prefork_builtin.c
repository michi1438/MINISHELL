/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_prefork_builtin.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:46:16 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/30 10:57:00 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pre_fork_builtin(char **cmd, t_minish *minish)
{
	if (minish->ppx.hd_on == 1 && cmd[0] == NULL)
		return (0);
	if (ft_strncmp(cmd[0], "cd\0", 3) == 0)
	{
		if (minish->ppx.n_cmd == 1)
			builtin_cd(cmd, minish);
		return (1);
	}
	else if (ft_strncmp(cmd[0], "export\0", 7) == 0)
	{
		if (minish->ppx.n_cmd == 1)
		{
			if (cmd[1] == NULL)
				export_noarg(minish);
			else
				builtin_export(cmd, minish);
		}
		return (1);
	}
	else if (ft_strncmp(cmd[0], "unset\0", 6) == 0)
	{
		minish->env = builtin_unset(cmd, minish);
		return (1);
	}
	else if (ft_strncmp(cmd[0], "exit\0", 5) == 0)
	{
		minish->ppx.last_exit_status = builtin_exit(cmd, minish);
		return (1);
	}
	else
		return (0);
}

char	**builtin_unset(char **cmd, t_minish *minish)
{
	int		j;
	int		i;
	int		e;
	char	*var;
	char	**new_env;

	j = 1;
	e = 0;
	while (cmd[j] != NULL)
	{
		i = 0;
		while (minish->env[i] != NULL)
		{
			var = ft_strjoin(cmd[j], "=");
			if (ft_strncmp(var, minish->env[i], ft_strlen(var)) == 0)
				e++;	
			i++;
		}
		j++;
	}
	new_env = ft_calloc(num_of_line(minish->env) - e, sizeof(char *));
	e = 0;
	j = 0;
	while (minish->env[j] != NULL)
	{
		i = 1;
		while (cmd[i] != NULL)
		{
			var = ft_strjoin(cmd[i], "=");
			if (ft_strncmp(var, minish->env[j], ft_strlen(var)) == 0)
			{
				j++;
				break ;
			}
			i++;
		}
		if (cmd[i] == NULL)
			new_env[e++] = ft_strdup(minish->env[j++]);
	}
	return (new_env);
}




int	builtin_exit(char **cmd, t_minish *minish)
{
	int i;

	i = 0;
	if (cmd[1] != NULL)
	{
		if (cmd[2] != NULL) 
		{
			printf("%s: too many arguments\n", cmd[0]);
			return (1);
		}
		while (cmd[1][i] != '\0')
		{
			if (!(ft_isdigit(cmd[1][i++])))
			{
				printf("%s: numeric argument required\n", cmd[1]);
				return (2);
			}
		}
		printf("exit\n");
		exit (ft_atoi(cmd[1]));
	}
	else
	{
		printf("exit\n");
		exit (minish->ppx.last_exit_status);
	}
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
			minish->ppx.last_exit_status = 1;	
			flg = 1;
		}
		else
		{
			minish->env = new_env_maker(cmd, minish, j);
			if (flg == 0)
				minish->ppx.last_exit_status = 0;
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
		if (chdir(cmd[1]) == -1)
		{
			minish->ppx.last_exit_status = 1;
			perror(cmd[1]);
		}
	}
	else
		chdir(check_env_var(minish->env, "HOME="));
}
