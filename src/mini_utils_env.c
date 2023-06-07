/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:51:57 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/07 16:06:27 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_copy_env(char *env[])
{
	int			i;
	static int	flg;
	char		**cpy_env;

	i = 0;
	while (env[i])
		i++;
	cpy_env = w_malloc_protect((i + 2) * sizeof(char *));
	if (cpy_env == NULL)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0 && flg == 0)
		{
			cpy_env[i] = change_shlvl(env[i]);
			flg = 1;
		}
		else
			cpy_env[i] = ft_strdup(env[i]);
	}
	if (flg != 1)
		cpy_env[i++] = ft_strdup("SHLVL=1");
	cpy_env[i] = NULL;
	return (cpy_env);
}

char	*change_shlvl(char *envline)
{
	int		i;
	int		val;
	char	*a_val;
	char	*ret;

	i = 0;
	while (envline[i] != '\0' && (!ft_isdigit(envline[i])))
		i++;
	if (envline[i] == '\0')
		val = 0 + 1;
	else
		val = ft_atoi(&envline[i]) + 1;
	ret = ft_substr(envline, 0, i);
	a_val = ft_itoa(val);
	ret = w_strjoin_rm_arg1(ret, a_val);
	free(a_val);
	return (ret);
}
