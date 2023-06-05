/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <lzito@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:27:56 by lzito             #+#    #+#             */
/*   Updated: 2023/06/05 10:10:35 by mguerga          ###   ########.fr       */
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
		var = gc_itoa(var);
	else
	{
		temp = gc_strjoin(var, "=");
		var = check_env_var(minish->env, temp);
	}
	*j = i[0] - 1;
	return (var);
}

int	is_dol_end(char *quote, int j)
{
	if ((ft_isdigit(quote[j - 1])
			|| quote[j - 1] == '?') && quote[j - 2] == '$')
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
	char	*temp;
	char	*value;

	j = 0;
	tot_size = 0;
	var = NULL;
	while (quote[j] != '\0')
	{
		if (quote[j++] == '$' && quote[0] != '\'')
		{
			i = j;
			while (is_dol_end(quote, j))
				j++;
			var = ft_substr(&quote[i], 0, j - (i));
			if (ft_strncmp(var, "?", 2) == 0)
			{
				temp = ft_itoa(g_exit_status);
				tot_size += ft_strlen(temp);
				free(var);
				free(temp);
			}
			else
			{	
				temp = gc_strjoin(var, "=");
				value = check_env_var(minish->env, temp);
				if (value != NULL)
				{
					tot_size += ft_strlen(value);
					free(value);
				}
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
