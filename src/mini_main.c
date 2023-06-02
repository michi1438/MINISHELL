/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <lzito@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:56:43 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/02 17:56:29 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char *av[], char *env[])
{
	t_minish	minish;

	(void) av;
	if (ac != 1 || ft_initmain(&minish, env) == 1)
		return (1);
	while (1)
	{
		init_minish(&minish);
		minish.line = readline("(ಠ.ಠ)¬ ");
		if (minish.line == NULL)
		{
			printf ("exit\n");
			exit (g_exit_status);
		}
		if (minish.line[0] != '\0' && is_all_space(minish.line) == 1)
			treating_line(&minish);
		ft_gc(NULL, DEL);
	}
	return (0);
}

int	ft_initmain(t_minish *minish, char **env)
{
	ft_signals_n_attr(SET);
	g_exit_status = 0;
	minish->prev_line = NULL;
	minish->env = ft_copy_env(env);
	if (minish->env == NULL)
		return (1);
	return (0);
}

int	init_minish(t_minish *minish)
{
	ft_signals_n_attr(RESET);
	minish->ppx.n_cmd = 1;
	minish->lst_line = NULL;
	return (0);
}

void	ft_add_history(t_minish *minish)
{
	size_t	l_line;

	l_line = ft_strlen(minish->line);
	if (minish->prev_line != NULL)
	{
		if (ft_strlen(minish->prev_line) > ft_strlen(minish->line))
		{
			l_line = ft_strlen(minish->prev_line);
			free(minish->prev_line);
		}
	}
	if (minish->prev_line == NULL || ft_strncmp(minish->line,
			minish->prev_line, l_line) != 0)
	{
		add_history(minish->line);
		minish->prev_line = ft_strdup(minish->line);
		if (minish->prev_line == NULL)
			return ;
		free(minish->prev_line);
	}
}

void	treating_line(t_minish *minish)
{
	ft_add_history(minish);
	if (ft_token(minish) != -1)
		g_exit_status = main_pipe(minish, &minish->ppx);
	else
	{
		printf("unexpected token ERROR\n");
		g_exit_status = 2;
	}
}

int	ft_token(t_minish *minish)
{
	int			i;
	const char	*tok[] = {
		"\'", "\"", "|", ">>", "<<", ">", "<", " ", NULL,
	};

	i = 0;
	while (minish->line[i] != '\0')
	{
		i = is_not_tokenable(minish, i, tok);
		i = is_tokenable(minish, i, tok);
		if (i == -1)
			return (-1);
		if (minish->line[i] != '\0')
			i++;
	}
	add_cmds(minish);
	return (ft_err_handling(minish));
}
