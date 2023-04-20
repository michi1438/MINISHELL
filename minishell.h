/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:25:53 by mguerga           #+#    #+#             */
/*   Updated: 2023/04/20 19:39:46 by mguerga          ###   ########.fr       */
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

enum e_gcstatus
{
	ADD,
	DEL,
};

int		main_pipe(int ac, char *av[], char *env[]);

//GARBAGE_COLLECTOR
void	*gc_malloc(size_t size, int status);
void	ft_gc(void *ptr, int status);

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
void	ft_looppid(t_pipex *ppx, char **env, int idx);
int		ft_feedppx(t_pipex *ppx, char **av, char **env);
int		ft_initppx(t_pipex *ppx, int ac, char *av[], char **env);
// MINIPIPE

#endif
