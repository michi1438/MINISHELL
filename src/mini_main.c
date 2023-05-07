/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <lzito@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:56:43 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/07 10:00:45 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char *av[], char *env[])
{
	t_minish			minish;

	(void) av;
	ft_signals_n_attr();
	minish.env = ft_copy_env(env);
	if (ac != 1 || minish.env == NULL)
		return (1);
	while (1)
	{
		init_minish(&minish);
		minish.line = readline("(ಠ.ಠ)¬ ");
		if (minish.line == NULL)
			return (0);
		if (minish.line[0] != '\0' && is_all_space(minish.line) == 1)
			treating_line(&minish);
	}
	return (0);
}

int	init_minish(t_minish *minish)
{
	minish->ppx.hd_on = 0;
	minish->ppx.app_on = 0;
	minish->ppx.f_in = 0;
	minish->ppx.f_out = 1;
	minish->ppx.n_cmd = 1;
	minish->lst_line = NULL;
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
		if (minish->line[i] != '\0')
			i++;
	}
	return (ft_err_handling(minish));
}

void	treating_line(t_minish *minish)
{
	add_history(minish->line);
	if (ft_token(minish) != -1)
	{
		add_cmds(minish);
		main_pipe(minish, &minish->ppx);
		mini_lstclear(&minish->lst_line, free);
	}
	else
		printf("unexpected token ERROR\n");
}

void	add_cmds(t_minish *minish)
{
	t_list		*lst;
	t_content	*cont;
	int			i;

	lst = minish->lst_line;
	minish->cmds = malloc(sizeof(char *) * (minish->ppx.n_cmd));
	i = 0;
	minish->cmds[i] = NULL;
	while (lst != NULL)
	{
		cont = lst->content;
		if (cont->type == OTHER)
		{
			minish->cmds[i] = cont->str;
		}  
		else if (cont->type == QUOTE)
		{
			if (minish->cmds[i] == NULL)
				minish->cmds[i] = ft_strtrim(cont->str, "'");
			else 
			{
				minish->cmds[i] = ft_strjoin(minish->cmds[i], " ");
				minish->cmds[i] = ft_strjoin(minish->cmds[i], ft_strtrim(cont->str, "\'"));
			}
		}
		else if (cont->type == DBLQUOTE)
		{
			if (minish->cmds[i] == NULL)
				minish->cmds[i] = ft_strtrim(cont->str, "\"");
			else 
			{
				minish->cmds[i] = ft_strjoin(minish->cmds[i], " ");
				minish->cmds[i] = ft_strjoin(minish->cmds[i], ft_strtrim(cont->str, "\""));
			}
		}
		else 
			i++;
		lst = lst->next;
	}
}
