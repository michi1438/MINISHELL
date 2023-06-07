/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:45:42 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/07 15:23:15 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_dol_end(char *quote, int j)
{
	if ((ft_isdigit(quote[j - 1])
			|| quote[j - 1] == '?') && quote[j - 2] == '$')
		return (0);
	if (quote[j] != ' ' && quote[j] != '\"' && quote[j] != '\0'
		&& quote[j] != '$' && quote[j] != '\'')
		return (1);
	return (0);
}

int	new_size(char *quote, t_minish *minish)
{
	int		i;
	int		j;
	int		tot_size;
	char	*var;

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
			size_dol_or_var(var, &tot_size, minish);
		}
		else
			tot_size++;
	}
	return (tot_size);
}

void	size_dol_or_var(char *var, int *size, t_minish *minish)
{
	char	*temp;
	char	*val;

	if (ft_strncmp(var, "?", 2) == 0)
	{
		temp = ft_itoa(g_exit_status);
		*size += ft_strlen(temp);
		free(var);
		free(temp);
	}
	else
	{	
		temp = w_strjoin_rm_arg1(var, "=");
		val = check_env_var(minish->env, temp);
		if (val != NULL)
		{
			*size += ft_strlen(val);
			free(val);
		}
	}
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
