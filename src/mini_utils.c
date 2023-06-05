/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <lzito@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:46:25 by lzito             #+#    #+#             */
/*   Updated: 2023/06/05 18:43:47 by mguerga          ###   ########.fr       */
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
	cpy_env = malloc((i + 2) * sizeof(char *));
	if (cpy_env == NULL)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0 && flg == 0)
		{
			cpy_env[i] = change_shlvl(env[i]);
			flg = 1;
		}
		else
			cpy_env[i] = ft_strdup(env[i]);
		i++;
	}
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

void	mini_lstdelone(t_list *node, void (*del)(void*))
{
	t_content	*cont;

	cont = node->content;
	if (node && del)
	{
		del(cont->str);
		del(cont);
		free(node);
	}
}

void	mini_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	temp = *lst;
	if (*lst && del)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			mini_lstdelone(*lst, del);
			*lst = temp;
		}
	}
}

int	is_prefork_builtin(char **cmd)
{
	int			i;
	const char	*builtin[] = {
		"exit", "cd", "unset", NULL,
	};

	i = 0;
	while (builtin[i] != NULL)
	{
		if (ft_strncmp(cmd[0], builtin[i], ft_strlen(builtin[i])) == 0)
			return (0);
		else if (ft_strncmp(cmd[0], "export\0", 7) == 0 && cmd[1] != NULL)
			return (0);
		i++;
	}
	return (-1);
}

int	num_of_line(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	return (i + 2);
}

int	ft_pre_free(t_minish *minish)
{
	int i;

	i = 0;
	if (!minish->cmds || !minish->cmds[i])
		return (-1);
	while (i < minish->ppx.n_cmd)
	{
		free(minish->cmds[i]);
		if (minish->ppx.filein != NULL && minish->ppx.filein[i] != NULL)
			free(minish->ppx.filein[i]);
		if (minish->ppx.fileout != NULL && minish->ppx.fileout[i] != NULL)
			free(minish->ppx.fileout[i]);
		if (minish->ppx.limiter != NULL && minish->ppx.limiter[i] != NULL)
			free(minish->ppx.limiter[i]);
		i++;
	}
	return (-1);
}
