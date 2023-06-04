/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:00:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/04 14:42:23 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_for_builtin(char **cmd, t_minish *minish, int i)
{
	if (cmd[0] == NULL)
	{
		if (minish->ppx.limiter[i] != NULL
			|| minish->ppx.filein[i] != NULL
			|| minish->ppx.fileout[i] != NULL)
			exit (0);
		return ;
	}
	if (ft_strncmp(cmd[0], "echo\0", 5) == 0)
		builtin_echo(cmd);
	else if (ft_strncmp(cmd[0], "pwd\0", 4) == 0)
		builtin_pwd();
	else if (ft_strncmp(cmd[0], "env\0", 4) == 0)
		builtin_env(minish, cmd);
	else if (ft_strncmp(cmd[0], "export\0", 7) == 0 && cmd[1] == NULL)
		export_noarg(minish);
}

void	builtin_env(t_minish *minish, char **cmd)
{
	int	i;

	i = 0;
	if (cmd[1] != NULL)
	{
		perror(cmd[1]);// TODO perror or not ?
		//printf("%s: No such file or directory\n", cmd[1]);
		exit(127);
	}
	else
	{
		while (minish->env[i] != NULL)
			printf("%s\n", minish->env[i++]);
	}
	exit (0);
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
	exit (0);
}

void	builtin_pwd(void)
{
	char	*ret;

	ret = getcwd(NULL, 0);
	if (!ret)
		exit (1);
	ft_putstr_fd(ret, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(ret);
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
		if (ft_strncmp(cmd[i], "-n", 2) == 0 && flg == 0 && i == 1)
			echo_option(cmd, &i, &flg);
		ft_putstr_fd(cmd[i], STDOUT_FILENO);
		if (cmd[(i++) + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (flg == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	exit (0);
}

void	echo_option(char **cmd, int *i, int *flg)
{
	int	j;

	while (ft_strncmp(cmd[*i], "-n", 2) == 0)
	{
		j = 2;
		while (cmd[*i][j] == 'n')
			j++;
		if (cmd[*i][j] == '\0')
		{
			(*flg) = 1;
			(*i)++;
		}
		else
			break ;
	}
}
