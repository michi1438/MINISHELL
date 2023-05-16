/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:58:25 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/16 15:40:31 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/src_libft.h"
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <termios.h> 

typedef struct s_pipex
{
	int		**fd;
	int		fd_hd[2];
	int		hd_on;
	int		app_on;
	char	*limiter;
	int		*pid;
	char	***cmd;
	int		f_in;
	int		f_out;
	char	**path;
	int		n_cmd;
}	t_pipex;

typedef struct s_minish
{
	char			**env;
	char			*line;
	char			*prev_line;
	char			**cmds;
	struct termios	oldtermi;
	t_list			*lst_line;
	t_pipex			ppx;
}	t_minish;

typedef struct s_content
{
	char	*str;
	int		type;
}	t_content;

enum e_tolkien
{
	QUOTE,
	DBLQUOTE,
	PIPE,
	APP_OUT,
	HERE_DOC,
	REDIR_OUT,
	REDIR_IN,
	SPCE,
	OTHER,
};

typedef struct s_gc
{
	int	flush;
}	t_gc;

enum e_gcstatus
{
	ADD,
	DEL,
	EXT,
};

// MINI_MAIN.C
int			init_minish(t_minish *minish);
int			ft_initmain(t_minish *minish, char **env);
int			ft_token(t_minish *minish);
void		treating_line(t_minish *minish);
void		ft_add_history(t_minish *minish);

// MINI_BUILTINS.C
void		check_for_builtin(char **cmd);
void		builtin_echo(char **cmd);

//FOR_TESTING_ONLY.C
void		print_lst_line(t_minish minish);

// MINI_TOKENABLE.C
int			is_tokenable(t_minish *minish, int i, const char *tok[]);
int			search_quotes(t_minish *minish, int type, int i);
int			deal_with_pipes(t_minish *minish, int i);
int			deal_with_redir(t_minish *minish, int type, int i);
int			deal_with_spaces(t_minish *minish, int i);

// MINI_NOT_TOKENABLE.C
int			is_not_tokenable(t_minish *minish, int i, const char *tok[]);
int			not_token_size(t_minish *minish, int i, const char *tok[]);
int			is_all_space(char *str);

// MINI_TOK_TO_PIPES.C
void		add_cmds(t_minish *minish);
void		append_or_start(t_minish *minish, char *strseg, char *tok_delimiter, int i);

// MINI_EXPAND.C
char		*expand_variables(char *dblquote, t_minish *minish);
void		treating_expand(char *quote, t_minish *minish, int *j, char *ret);
int			new_size(char *quote, t_minish *minish);
char		*check_env_var(char **env, char *var);

// MINI_UTILS.C
char		**ft_copy_env(char *env[]);
void		mini_lstdelone(t_list *node, void (*del)(void*));
void		mini_lstclear(t_list **lst, void (*del)(void*));

// MINI_ERRORS.C
int			ft_err_handling(t_minish *minish);

// MINI_GC.C
void		*gc_malloc(size_t size);
void		gc_free(void *ptr);
void		*ft_gc(void *garb, int status);
void		gc_lstdelone(t_list *lst, void (*del)(void*));
void		gc_lstclear(t_list **lst, void (*del)(void*));

// MINI_SIG_N_ATTR.C
void		ft_signals_n_attr(t_minish *minish);
void		set_act_int(struct sigaction *act_int);
void		set_act_quit(struct sigaction *act_quit);
void		re_prompt(int useless);

// MINIPIPE
//ppx_checks.c
char		*ft_checkexe(char **paths, char *cmd);
char		**ft_checkenv(char *env[]);
char		*ft_checkpath(char *env[], char *cmd);

//ppx_free.c
void		ft_freeall(t_pipex *ppx);
void		ft_free(char **av);
int			ft_waitnclose(t_pipex *ppx);
void		ft_close_fds(t_pipex *ppx);

//ppx_utils.c
int			ft_error(char *error, int errn);
void		ft_dup(int in, int out);
int			ft_stralnum(char *str);

//ppx_hd.c
void		ft_checkheredoc(char **av, t_pipex *ppx);
int			ft_heredoc(t_pipex *ppx);

//ppx_main.c
int			main_pipe(t_minish *minish, t_pipex *ppx);
void		ft_looppid(t_pipex *ppx, t_minish *minish, int idx);
int			ft_feedppx(t_pipex *ppx, char **av, char **env);
int			ft_initppx(t_pipex *ppx, t_minish *minish);

//RL respecified proto for norminette 
//(not actually used because of the -I in Makefile CFLAGS)
extern void	rl_replace_line(const char *s, int i);

#endif
