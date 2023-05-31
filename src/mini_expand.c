/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <lzito@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:27:56 by lzito             #+#    #+#             */
/*   Updated: 2023/05/31 09:21:51 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_variables(char *quote, t_minish *minish)
{
	int		j;
	char	*ret;

	j = 0;
	ret = ft_calloc(new_size(quote, minish) + 1, sizeof(char));
	while (quote[j] != '\0')
	{
		if (quote[j] == '$' && quote[0] != '\'')
			treating_expand(quote, minish, &j, ret);
		else
			ret[ft_strlen(ret)] = quote[j++];
	}
	free (quote);
	ret = escape_spaces(ret);
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
	while (is_dol_end(quote, *j))
		(*j)++;
	var = ft_substr(&quote[i], 0, *j - i);
	lendllr = ft_strlen(var) + 1;
	if (ft_strncmp(var, "?", 2) == 0)
		var = ft_itoa(minish->ppx.exit_status);
	else
	{
		var = ft_strjoin_n_free(var, "=");
		var = check_env_var(minish->env, var); // TODO var, is going to cause leaks
	}
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

int	is_dol_end(char *quote, int j)
{
	if ((ft_isdigit(quote[j - 1]) || quote[j - 1] == '?') && quote[j - 2] == '$')
		return (0);
	if (quote[j] != ' ' && quote[j] != '\"' && quote[j] != '\0'
		&& quote[j] != '$')
		return (1);
	return (0);
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
		if (quote[j++] == '$' && quote[0] != '\'')
		{
			i = j;
			while (is_dol_end(quote, j))
				j++;
			var = ft_substr(&quote[i], 0, j - (i));
			if (ft_strncmp(var, "?", 2) == 0)
				tot_size += ft_strlen(ft_itoa(minish->ppx.exit_status));
			else
			{	
				value = check_env_var(minish->env, ft_strjoin(var, "=")); // TODO, var is going to cause leaks
				if (value != NULL)
					tot_size += ft_strlen(value);
			}
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

int	escaped_size(char *ret)
{
	int		j;
	int		tot_size;

	j = 0;
	tot_size = 0;
	while (ret[j] != '\0')
	{
		if (ret[j++] == ' ')
			tot_size += 2;
		else
			tot_size++;
	}
	return (tot_size);
}

char	*escape_spaces(char *ret)
{
	int		i;
	int		j;
	char	*newret;

	j = 0;
	i = 0;
	newret = ft_calloc((escaped_size(ret) + 1), sizeof(char));
	if (newret == NULL)
	{
		printf("alloc failed\n");
		exit (100); // TODO protect, and bring it back up
	}
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
