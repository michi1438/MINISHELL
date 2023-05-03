/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:58:25 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/03 15:39:02 by lzito            ###   ########.fr       */
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

// MAIN
typedef struct s_minish
{
	char	**env;
	int		n_cmd;
	int		is_hd;
	char	*line;
	t_list	*lst_line;
}	t_minish;

int		init_minish(t_minish *minish, char *env[]);

//TESTING
void	print_lst_line(t_minish minish);

// TOlKiEN
int		ft_token(t_minish *minish);
int		search_quotes(t_minish *minish, int type, int i);
int		deal_with_pipes(t_minish *minish, int i);
int		deal_with_redir(t_minish *minish, int type, int i);
int		is_tokenable(t_minish *minish, int i, const char *tok[]);
int		is_not_tokenable(t_minish *minish, int i, const char *tok[]);
int		not_token_size(t_minish *minish, int i, const char *tok[]);
int		deal_with_other(t_minish *minish, int type, int i);
int		is_all_space(char *str);

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
	ENV_VAR,
	OTHER,
};

// UTILS
char	**ft_copy_env(char *env[]);
void	mini_lstdelone(t_list *node, void (*del)(void*));
void	mini_lstclear(t_list **lst, void (*del)(void*));

//GARBAGE_COLLECTOR
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

void	*gc_malloc(size_t size);
void	gc_free(void *ptr);
void	*ft_gc(void *garb, int status);
void	gc_lstdelone(t_list *lst, void (*del)(void*));
void	gc_lstclear(t_list **lst, void (*del)(void*));

//SIGNALS
void	ft_signals(void);
void	set_act_int(struct sigaction *act_int);
void	set_act_quit(struct sigaction *act_quit);
void	re_prompt(int useless);

// MINIPIPE
typedef struct s_pipex
{
	int		**fd;
	int		fd_hd[2];
	int		hd_on;
	char	*limiter;
	int		*pid;
	char	***cmd;
	int		f_in;
	int		f_out;
	char	**path;
	int		n_cmd;
}	t_pipex;

//ppx_checks.c
char	*ft_checkexe(char **paths, char *cmd);
char	**ft_checkenv(char *env[]);
char	*ft_checkpath(char *env[], char *cmd);

//ppx_free.c
void	ft_freeall(t_pipex *ppx);
void	ft_free(char **av);
int		ft_waitnclose(t_pipex *ppx);
void	ft_close_fds(t_pipex *ppx);

//ppx_utils.c
int		ft_error(char *error, int errn);
void	ft_dup(int in, int out);
int		ft_stralnum(char *str);

//ppx_hd.c
void	ft_checkheredoc(char **av, t_pipex *ppx);
int		ft_heredoc(t_pipex *ppx);

//ppx_main.c
int		main_pipe(int ac, char *av[], char *env[]);
void	ft_looppid(t_pipex *ppx, char **env, int idx);
int			ft_feedppx(t_pipex *ppx, char **av, char **env);
int			ft_initppx(t_pipex *ppx, int ac, char *av[], char **env);

//RL respecified proto for norminette 
//(not actually used because of the -I in Makefile CFLAGS)
extern void	rl_replace_line(const char *s, int i);

#endif
