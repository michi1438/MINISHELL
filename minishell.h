/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:43:13 by mguerga           #+#    #+#             */
/*   Updated: 2023/04/19 20:47:19 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

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
