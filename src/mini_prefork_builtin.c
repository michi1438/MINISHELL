/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_prefork_builtin.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:46:16 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/30 19:13:18 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pre_fork_builtin(char **cmd, t_minish *minish)
{
	if (cmd[0] == NULL)
		return (0);
//	if (minish->ppx.hd_on[i] == 1 && cmd[0] == NULL)
//		return (0);
	if (ft_strncmp(cmd[0], "cd\0", 3) == 0)
	{
		if (minish->ppx.n_cmd == 1)
			builtin_cd(cmd, minish);
	}
	else if (ft_strncmp(cmd[0], "export\0", 7) == 0)
	{
			if (cmd[1] == NULL)
				return (0);
			else if (minish->ppx.n_cmd == 1)
				builtin_export(cmd, minish);
	}
	else if (ft_strncmp(cmd[0], "unset\0", 6) == 0)
		minish->env = builtin_unset(cmd, minish);
	else if (ft_strncmp(cmd[0], "exit\0", 5) == 0)
		minish->ppx.exit_status = builtin_exit(cmd, minish);
	else
		return (0);
	return (1);
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
		i = 1;
		while (cmd[i] != NULL)
		{
			var = ft_strjoin(cmd[i], "=");
			if (ft_strncmp(var, minish->env[j++], ft_strlen(var)) == 0)
				break ;
			i++;
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
		exit (minish->ppx.exit_status);
	}
}

void	builtin_cd(char **cmd, t_minish *minish)
{
	if (cmd[1] != NULL)
	{
		if (chdir(cmd[1]) == -1)
		{
			minish->ppx.exit_status = 1;
			perror(cmd[1]);
		}
	}
	else
		chdir(check_env_var(minish->env, "HOME="));
}
