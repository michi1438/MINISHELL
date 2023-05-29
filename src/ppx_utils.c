/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <lzito@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 20:27:24 by lzito             #+#    #+#             */
/*   Updated: 2023/05/29 14:31:18 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_error(char *error, int errn)
{
	perror(error);
	return (errn);
}

void	ft_dup(int in, int out)
{
	if (dup2(in, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(out, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
}

int	ft_stralnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
