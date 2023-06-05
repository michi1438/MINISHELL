/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <lzito@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:27:56 by lzito             #+#    #+#             */
/*   Updated: 2023/06/05 18:34:59 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_variables(char *quote, t_minish *minish)
{
	int		j;
	char	*ret;

	j = 0;
	ret = ft_calloc(new_size(quote, minish) + 1, sizeof(char));
	if (!ret)
		return (NULL);
	while (quote[j] != '\0')
	{
		if (quote[j] == '$' && quote[0] != '\'')
			treating_expand(quote, minish, &j, ret);
		else
			ret[ft_strlen(ret)] = quote[j++];
	}
	free(quote);
	ret = escape_spaces(ret);
	return (ret);
}

void	treating_expand(char *quote, t_minish *minish, int *j, char *ret)
{
	int		i[2];
	char	*var;

	i[0] = 0;
	(*j)++;
	i[0] = *j;
	while (is_dol_end(quote, *j))
		(*j)++;
	var = find_var(minish, quote, i, j);
	i[0] = 0;
	if (var != NULL)
	{
		while (var[i[0]] != '\0')
		{
			ret[ft_strlen(ret)] = var[i[0]++];
			(*j)++;
		}
		free(var);
	}
	*j = (*j - i[0]) + i[1];
}

char	*find_var(t_minish *minish, char *quote, int i[2], int *j)
{
	char	*var;
	char	*temp;

	i[1] = 0;
	var = ft_substr(&quote[i[0]], 0, *j - i[0]);
	i[1] = ft_strlen(var) + 1;
	if (ft_strncmp(var, "?", 2) == 0)
		var = w_itoa_rm(var);
	else
	{
		temp = w_strjoin_rm_arg1(var, "=");
		var = check_env_var(minish->env, temp);
	}
	*j = i[0] - 1;
	return (var);
}

char	*check_env_var(char **env, char *var)
{
	int		i;	
	char	*envline;
	char	*temp;

	i = 0;
	envline = NULL;
	while (env[i] != NULL)
	{
		envline = ft_strnstr(env[i], var, ft_strlen(var));
		if (envline != NULL)
		{
			temp = ft_strdup(&envline[ft_strlen(var)]);
			free(var);
			return (temp);
		}
		i++;
	}
	free(var);
	return (NULL);
}

char	*escape_spaces(char *ret)
{
	int		i;
	int		j;
	char	*newret;

	j = 0;
	i = 0;
	//TODO MALLOC A PROTEGER !!!
	newret = ft_calloc((escaped_size(ret) + 1), sizeof(char));
	if (newret == NULL)
		return (NULL);
	while (ret[j] != '\0')
	{
		if (ret[j] == ' ')
			newret[i++] = '\\';
		newret[i++] = ret[j++];
	}
	newret[i] = '\0';
	free (ret);
	return (newret);
}
