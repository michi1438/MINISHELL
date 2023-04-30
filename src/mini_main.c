/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <lzito@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:56:43 by mguerga           #+#    #+#             */
/*   Updated: 2023/04/30 17:23:47 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char *av[], char *env[])
{
	t_minish	minish;

	(void) av;
	ft_signals();
	if (ac != 1)
		return (1);
	minish.env = ft_copy_env(env);
	if (minish.env == NULL)
		return (1);
	while (1)
	{
		minish.line = readline("(ಠ.ಠ)¬ ");
		ft_gc(minish.line, ADD);
		if (minish.line == NULL)
		{
			ft_gc(NULL, DEL);
			return (0);
		}
		if (minish.line[0] != '\0')
			add_history(minish.line);
		if (ft_token(&minish) == -1)
			printf("unexpected token ERROR\n");
	}
	return (0);
}

int	ft_token(t_minish *minish)
{
	int			i;
	const char	*tok[] = {
		"\'", "\"", "|", ">>", "<<", ">", "<", "$", NULL,
	};

	i = 0;
	while (minish->line[i] != '\0')
	{
		i = is_not_tokenable(minish, i, tok);
		i = is_tokenable(minish, i, tok);
		if (i == -1)
			return (-1);
		i++;
	}
	return (1);
}
