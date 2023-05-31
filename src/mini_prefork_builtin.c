/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_prefork_builtin.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:46:16 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/31 14:36:01 by mguerga          ###   ########.fr       */
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

int	builtin_exit(char **cmd, t_minish *minish)
{
	int	i;

	i = 0;
	if (cmd[1] != NULL)
	{
		if (cmd[2] != NULL)
			return (builtin_exit_err(cmd, 1));
		while (cmd[1][i] != '\0')
		{
			if (!(ft_isdigit(cmd[1][i++])))
				return (builtin_exit_err(cmd, 2));
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

int	builtin_exit_err(char **cmd, int err_type)
{
	if (err_type == 1)
	{
		printf("%s: too many arguments\n", cmd[0]);
		return (1);
	}
	else if (err_type == 2)
	{
		printf("%s: numeric argument required\n", cmd[1]);
		exit (2);
		// return (2); TODO
	}
	return (0);
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
