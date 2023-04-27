/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <lzito@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:56:43 by mguerga           #+#    #+#             */
/*   Updated: 2023/04/27 21:15:01 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parse(t_minish *minish)
{
	if (ft_token(minish) == -1)
		return (-1);
	return (1);
}

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
		if (minish.line == NULL)
			return (0);
		if (minish.line[0] != '\0')
			add_history(minish.line);
		if (ft_parse(&minish) == -1)
			printf("unexpected token ERROR\n");
		free(minish.line);
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

int	is_not_tokenable(t_minish *minish, int i, const char *tok[10])
{
	int	size;

	size = not_token_size(minish, i, tok);
	if (size > 0)
	{
		printf("%s\n", ft_substr(&minish->line[i], 0, size));
	}
	return (i + size);
}	

int	not_token_size(t_minish *minish, int i, const char *tok[10])
{
	int		size;
	int		j;

	size = 0;
	while (minish->line[i] != '\0')
	{
		j = 0;
		while (tok[j] != NULL)
		{
			if (ft_strncmp(&minish->line[i], tok[j], ft_strlen(tok[j])) == 0)
			{
				return (size);
			}
			else
				j++;
		}
		if (tok[j] == NULL || j == 8)
		{
			size++;
			i++;
		}
	}
	return (size);
}

int	is_tokenable(t_minish *minish, int i, const char *tok[10])
{
	int		j;

	j = 0;
	while (tok[j] != NULL)
	{
		if (ft_strncmp(&minish->line[i], tok[j], ft_strlen(tok[j])) == 0)
		{
			if (j == 0 || j == 1)
				return (search_quotes(minish->line, j, i));
			else if (j == 2)
				return (deal_with_pipes(minish, i));
			else if (j <= 6 && j >= 3)
				return (deal_with_redir(minish->line, j, i));
			else
				return (deal_with_other(minish, j, i));
		}
		j++;
	}
	return (i);
}

int	search_quotes(char *line, int type, int i)
{
	int		j;
	char	c;

	j = i;
	c = '"';
	if (type == 0)
		c = '\'';
	i++;
	while (line[i] != c)
	{
		if (line[i] == '\0')
			return (-1);
		i++;
	}
	printf("%s\n", ft_substr(&line[j], 0, (i + 1) - j));
	return (i);
}

int	deal_with_pipes(t_minish *minish, int i)
{
	minish->n_cmd++;
	printf("|\n");
	return (i);
}

int	deal_with_redir(char *line, int type, int i)
{
	int	j;

	j = i;
	if (type < 5)
		i++;
	printf("%s\n", ft_substr(&line[j], 0, (i + 1) - j));
	return (i);
}

int	deal_with_other(t_minish *minish, int type, int i)
{
	(void)minish;
	if (type == 7)
		printf("$\n");
	return (i);
}
