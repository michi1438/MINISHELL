/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:58:25 by mguerga           #+#    #+#             */
/*   Updated: 2023/05/02 15:01:53 by lzito            ###   ########.fr       */
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
	char	*line;
	t_list	**lst_line;
}	t_minish;

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

// UTILS
char	**ft_copy_env(char *env[]);

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
int		ft_feedppx(t_pipex *ppx, char **av, char **env);
int		ft_initppx(t_pipex *ppx, int ac, char *av[], char **env);

#endif
