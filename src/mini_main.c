/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <lzito@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:56:43 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/03 13:11:46 by mguerga          ###   ########.fr       */
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
		if (minish.line[0] != '\0')
			add_history(minish.line);
		if (ft_token(&minish) == -1)
			printf("unexpected token ERROR\n");
		print_lst_line(minish);
		ft_lstclear(&minish.lst_line, free);
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
		if (minish->line[i] != '\0')
			i++;
	}
	return (0);
}

void	print_lst_line(t_minish minish)
{
	t_list	*lst;

	lst = minish.lst_line;
	while (lst != NULL)
	{
		printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
}

int	init_minish(t_minish *minish, char *env[])
{
	minish->lst_line = NULL;
	minish->env = ft_copy_env(env);
	if (minish->env == NULL)
		return (1);
	return (0);
}
