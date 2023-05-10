/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <lzito@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:27:56 by lzito             #+#    #+#             */
/*   Updated: 2023/05/10 20:41:05 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_variables(char *quote, t_minish *minish)
{
	int		j;
	char	*ret;

	j = 0;
	ret = ft_calloc((new_size(quote, minish) + 1), sizeof(char));
	while (quote[j] != '\0')
	{
		if (quote[j] == '$')
			treating_expand(quote, minish, &j, ret);
		else
			ret[ft_strlen(ret)] = quote[j++];
	}
	return (ret);
}

void	treating_expand(char *quote, t_minish *minish, int *j, char *ret)
{
	int		i;
	char	*var;
	int		lendllr;

	i = 0;
	lendllr = 0;
	(*j)++;
	i = *j;
	while (quote[*j] != ' ' && quote[*j] != '\"' && quote[*j] != '\0')
		(*j)++;
	var = ft_substr(&quote[i], 0, *j - i);
	lendllr = ft_strlen(var) + 1;
	var = ft_strjoin(var, "=");
	var = check_env_var(minish->env, var);
	*j = i - 1;
	i = 0;
	if (var != NULL)
	{
		while (var[i] != '\0')
		{
			ret[ft_strlen(ret)] = var[i++];
			(*j)++;
		}
	}
	*j = (*j - i) + lendllr;
}

int	new_size(char *quote, t_minish *minish)
{
	int		i;
	int		j;
	int		tot_size;
	char	*var;
	char	*value;

	j = 0;
	tot_size = 0;
	while (quote[j] != '\0')
	{
		if (quote[j++] == '$')
		{
			i = j;
			while (quote[j] != ' ' && quote[j] != '\"' && quote[j] != '\0')
				j++;
			var = ft_substr(&quote[i], 0, j - (i));
			value = check_env_var(minish->env, ft_strjoin(var, "="));
			if (value != NULL)
				tot_size += ft_strlen(value);
		}
		else
			tot_size++;
	}
	return (tot_size);
}

char	*check_env_var(char **env, char *var)
{
	int		i;	
	char	*envline;

	i = 0;
	envline = NULL;
	while (env[i] != NULL)
	{
		envline = ft_strnstr(env[i], var, ft_strlen(var));
		if (envline != NULL)
			return (&envline[ft_strlen(var)]);
		i++;
	}
	return (NULL);
}
