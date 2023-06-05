/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_wraps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:22:33 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/05 14:36:51 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*w_strjoin_rm_arg1(char *s1, char *s2)
{
	void	*temp;

	temp = ft_strjoin(s1, s2);
	free(s1);
	return (temp);
}
