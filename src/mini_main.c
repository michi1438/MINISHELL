/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <lzito@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:56:43 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/10 15:20:11 by lzito            ###   ########.fr       */
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
	minish->cmds = ft_calloc(minish->ppx.n_cmd, sizeof(char *));
	i = 0;
	while (lst != NULL)
	{
		cont = lst->content;
		if (cont->type == OTHER)
			append_or_start(minish, cont->str, NULL, i);
		else if (cont->type == QUOTE)
			append_or_start(minish, cont->str, "'", i);
		else if (cont->type == DBLQUOTE)
		{
			cont->str = expand_variables(cont->str, minish);
			append_or_start(minish, cont->str, "\"", i);
		}
		else 
			i++;
		lst = lst->next;
	}
}

char	*expand_variables(char *quote, t_minish *minish)
{
	int		i;
	int		j;
	int		e;
	char	*ret;
	char	*var;

	j = 0; 
	i = 0;
	e = 0;
	ret = malloc((new_size(quote, minish) + 1) * sizeof(char));
	while (quote[j - e] != '\0')
	{
		printf("PASSSS\n");
		if (quote[j - e] == '$')
		{
			j++;
			i = j;
			while (quote[j - e] <= 'Z' && quote[j - e] >= 'A')
				j++;	
			var = ft_substr(&quote[i], 0, j - i);
			if (ft_strlen(var) > 0) 
				e += ft_strlen(var);
			var = ft_strjoin(var, "=");
			var = check_env_var(minish->env, var);
			j = i;
			i = 0;
			j--;
			while (var[i] != '\0')
				ret[j++] = var[i++];		
		}
		else
		{
			//printf("ret = %s\n", ret);
			ret[j] = quote[j - e]; 
			j++;
		}
	}
	ret[j] = '\0';
	return (ret);
}

int	new_size(char *quote, t_minish *minish)
{
	int		i;
	int		j;
	int		tot_size_var;
	int		tot_size_before;
	char	*var;

	j = 0; 
	tot_size_var = 0;
	tot_size_before = 0;
	while (quote[j] != '\0')
	{
		if (quote[j] == '$')
		{
			j++;
			i = j;
			while (quote[j] <= 'Z' && quote[j] >= 'A')
				j++;	
			var = ft_substr(&quote[i], 0, j - (i));
			tot_size_var += ft_strlen(check_env_var(minish->env, ft_strjoin(var, "=")));
		}
		else
		{
			j++;
			tot_size_before++;
		}
	}
	return (tot_size_before + tot_size_var);
}

char	*check_env_var(char **env, char *var)
{
	int		i;	
	char	*envline;
	
	i = 0;
	envline = NULL;
	while (env[i] != NULL)
	{
		envline = ft_strnstr(env[i], var, ft_strlen(var));
		if (envline != NULL)
			return (&envline[ft_strlen(var)]);
		i++;
	}
	return (NULL);
}

void	append_or_start(t_minish *minish, char *strseg, char *tok_delimiter, int i)
{
	if (minish->cmds[i] == NULL)
	{
		if (tok_delimiter == NULL) 
			minish->cmds[i] = strseg;
		else
			minish->cmds[i] = ft_strtrim(strseg, tok_delimiter);
	}
	else
	{
		if (tok_delimiter == NULL) 
		{
			minish->cmds[i] = ft_strjoin(minish->cmds[i], " ");
			minish->cmds[i] = ft_strjoin(minish->cmds[i], strseg);
		}
		else
		{
			minish->cmds[i] = ft_strjoin(minish->cmds[i], " ");
			minish->cmds[i] = ft_strjoin(minish->cmds[i], ft_strtrim(strseg, tok_delimiter));
		}
	}
}
