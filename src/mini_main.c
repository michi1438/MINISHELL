/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <lzito@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:56:43 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/03 21:35:00 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char *av[], char *env[])
{
	t_minish			minish;
	struct termios		termi;

	(void) av;
	ft_signals();
	tcgetattr(0, &termi);
	termi.c_lflag = ECHO;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termi);
	if (ac != 1)
		return (1);
	if (init_minish(&minish, env) != 0)
	{
		printf("init_failed ERROR\n");
		exit(1);
	}
	while (1)
	{
		minish.line = readline("(ಠ.ಠ)¬ ");
		if (minish.line == NULL)
			return (0);
		if (minish.line[0] != '\0' && is_all_space(minish.line) == 1)
		{
			add_history(minish.line);
			if (ft_token(&minish) == -1)
				printf("unexpected token ERROR\n");
			add_cmds(&minish);
			main_pipe(&minish, &minish.ppx);
			mini_lstclear(&minish.lst_line, free);
		}
	}
	return (0);
}

void	add_cmds(t_minish *minish)
{
	t_list		*lst;
	t_content	*cont;
	int			i;

	lst = minish->lst_line;
	minish->cmds = malloc(sizeof(char *) * (minish->ppx.n_cmd));
	i = 0;
	while (lst != NULL)
	{
		cont = lst->content;
		if (cont->type == OTHER)
		{
			minish->cmds[i] = cont->str;
			i++;
		}
		lst = lst->next;
	}
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
	return (0);
}

void	print_lst_line(t_minish minish)
{
	t_list		*lst;
	t_content	*cont;

	lst = minish.lst_line;
	while (lst != NULL)
	{
		cont = lst->content;
		printf("%s\n", cont->str);
		printf("%d\n", cont->type);
		lst = lst->next;
	}
}

int	init_minish(t_minish *minish, char *env[])
{
	minish->ppx.hd_on = 0;
	minish->ppx.app_on = 0;
	minish->ppx.f_in = 0;
	minish->ppx.f_out = 1;
	minish->ppx.n_cmd = 1;
	minish->n_pipe = 0;
	minish->lst_line = NULL;
//	minish->env = ft_copy_env(env);
	minish->env = env;
	if (minish->env == NULL)
		return (1);
	return (0);
}
