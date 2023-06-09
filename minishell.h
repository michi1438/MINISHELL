/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:58:25 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/07 17:36:07 by mguerga          ###   ########.fr       */
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

extern int	g_exit_status;
//int	g_exit_status;

typedef struct s_pipex
{
	int		**fd;
	int		**fd_hd;
	int		*hd_on;
	int		*app_on;
	int		*pid;
	char	***cmd;
	char	**limiter;
	char	**filein;
	char	**fileout;
	int		*f_in;
	int		*f_out;
	char	**path;
	int		n_cmd;
}	t_pipex;

typedef struct s_minish
{
	char		**env;
	char		*line;
	char		*prev_line;
	char		**cmds;
	t_list		*lst_line;
	t_pipex		ppx;
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

enum e_signal
{
	SET,
	RESET,
	NO_REPROMPT,
	UNSET,
	HD,
};

// MINI_MAIN.C
int			ft_token(t_minish *minish);
void		treating_line(t_minish *minish);
void		ft_add_history(t_minish *minish);

// MINI_INIT.C
int			ft_initmain(t_minish *minish, char **env);
int			init_minish(t_minish *minish);

// MINI_MOD_SPLIT.C
char		**ft_mod_split(char const *s, char c);
int			mini_counter(char const *s, char c);
void		*mini_implfing(char const *s, char c, char **ptrptr, int *i);
void		count_spaces_n_buf(const char *s, int *i, int *buf, int *space);
int			mini_clear_fing(char **ptrptr, int j);

// MINI_BUILTINS.C
void		check_for_builtin(char **cmd, t_minish *minish, int i);
void		builtin_env(t_minish *minish, char **cmd);
void		builtin_pwd(void);
void		export_noarg(t_minish *minish);

// MINI_BUILTINS_ECHO.C
void		builtin_echo(char **cmd);
void		echo_option(char **cmd, int *i, int *flg);

// MINI_PREFORK_BUILTIN.C
int			pre_fork_builtin(char **cmd, t_minish *minish);
int			builtin_exit(char **cmd);
int			builtin_exit_err(char **cmd, int err_type);
void		builtin_cd(char **cmd, t_minish *minish);

// MINI_PREFORK_EXPORT.C
void		builtin_export(char **cmd, t_minish *minish);
char		**new_env_maker(char **cmd, t_minish *minish, int j);
char		**alloc_env(t_minish *minish, char *cmd, int *i, char *temp[2]);

// MINI_PREFORK_UNSET.C
char		**builtin_unset(char **cmd, t_minish *minish);
int			testing_var(t_minish *minish, char **cmd, int *j);
int			new_env_size(char **cmd, t_minish *minish);

//FOR_TESTING_ONLY.C
void		print_lst_line(t_minish minish);

// MINI_TOKENABLE.C
int			is_tokenable(t_minish *minish, int i, const char *tok[]);
int			search_quotes(t_minish *minish, int type, int i);
int			no_other_quote(char *line, int *i, char c);
int			deal_with_pipes(t_minish *minish, int i);
int			deal_with_spaces(t_minish *minish, int i);

// MINI_REDIR.C
int			ft_heredoc(t_pipex *ppx, int i);
int			redir_quotes(int i, char *line);
void		redir_fill(t_minish *minish, int type, char *res, int i);
void		redondant_op(char **op, int i, char *res);
int			deal_with_redir(t_minish *minish, int type, int i);

// MINI_REDIR_CMDS.C
void		ft_redir_only_cmd(t_pipex *ppx, int idx);
void		ft_redir_first_cmd(t_pipex *ppx, int idx);
void		ft_redir_mid_cmd(t_pipex *ppx, int idx);
void		ft_redir_last_cmd(t_pipex *ppx, int idx);

// MINI_NOT_TOKENABLE.C
int			is_not_tokenable(t_minish *minish, int i, const char *tok[]);
int			not_token_size(t_minish *minish, int i, const char *tok[]);
int			is_all_space(char *str);

// MINI_APPEND_OR_START.C
void		append_or_start(t_minish *minish, char *strseg, char *delim, int i);
void		append(t_minish *minish, char *strseg, char *delim, int i);

// MINI_INIT_ADD_CMDS.C
int			init_cmds(t_minish *minish);
void		add_cmds(t_minish *minish);
void		add_redirs(t_content *cont, t_minish *minish, int i);
void		words_concat(t_content *cont, t_minish *minish, int i);

// MINI_EXPAND.C
char		*expand_variables(char *dblquote, t_minish *minish);
void		treating_expand(char *quote, t_minish *minish, int *j, char *ret);
char		*find_var(t_minish *minish, char *quote, int i[2], int *j);
char		*check_env_var(char **env, char *var);
char		*escape_spaces(char *ret);

// MINI_EXPAND_SIZE.C
int			is_dol_end(char *quote, int j);
int			new_size(char *quote, t_minish *minish);
void		size_dol_or_var(char *var, int *size, t_minish *minish);
int			escaped_size(char *ret);

// MINI_UTILS.C
char		**ft_copy_env(char *env[]);
char		*change_shlvl(char *env);
void		mini_lstdelone(t_list *node, void (*del)(void*));
void		mini_lstclear(t_list **lst, void (*del)(void*));
int			is_prefork_builtin(char **cmd);
int			num_of_line(char **env);
int			ft_pre_free(t_minish *minish);

// MINI_ERRORS.C
int			ft_err_handling(t_minish *minish);
t_list		*counting_cmd(int *i, t_list *lst);

// MINI_GC.C
void		*gc_malloc(size_t size);
void		*ft_gc(void *garb, int status);
void		gc_lstdelone(t_list *lst, void (*del)(void*));
void		gc_lstclear(t_list **lst, void (*del)(void*));
void		free_double(char **env);

// MINI_WRAPS.C
char		*w_strjoin_rm_arg1(char *s1, char *s2);
char		*w_itoa_rm(char *var);
void		*w_malloc_protect(size_t size);
void		*w_ft_calloc_prot(int nmemb, size_t size);

// MINI_SIG_N_ATTR.C
void		ft_signals_n_attr(int toggle);
void		set_act_int(struct sigaction *act_int, int toggle);
void		set_act_quit(struct sigaction *act_quit, int toggle);

// MINI_SA_HANDLER.C
void		no_re_prompt_bs(int useless);
void		no_re_prompt(int useless);
void		re_prompt(int useless);

// MINI_EXIT_STATUS.C
void		update_exit_stat(char *fullpath, t_pipex *ppx, char *cmd);

// MINIPIPE
//ppx_checks.c
char		*ft_checkexe(char **paths, char *cmd);
char		**ft_checkenv(char *env[]);
char		*ft_checkpath(char *env[], char *cmd);

//ppx_free.c
void		ft_freeloop(t_pipex *ppx);
void		ft_freeall(t_pipex *ppx);
void		ft_free(char **av);
int			ft_waitnclose(t_pipex *ppx);
void		ft_close_fds(t_pipex *ppx);

//ppx_utils.c
int			ft_error(char *error, int errn);
void		ft_dup(int in, int out);
int			ft_stralnum(char *str);

//ppx_main.c
void		ft_looppid(t_pipex *ppx, t_minish *minish, int idx);
int			ft_feedppx(t_pipex *ppx, char **av, char **env);
int			feed_err(char **av, t_pipex *ppx, char **env, int *i);
int			main_pipe(t_minish *minish, t_pipex *ppx);

//ppx_init.c
int			ft_initppx(t_pipex *ppx, t_minish *minish);
int			ft_initppx_io(t_pipex *ppx);
int			init_f_out(t_pipex *ppx, int i);

//RL respecified proto for norminette 
//(not actually used because of the -I in Makefile CFLAGS)
extern void	rl_replace_line(const char *s, int i);

#endif
