/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <lzito@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 20:21:48 by lzito             #+#    #+#             */
/*   Updated: 2023/05/30 23:27:41 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*ft_checkexe(char **paths, char *cmd)
{
	int		i;
	char	*newpath;
	char	*fullpath;

	i = 0;
	while (paths[i])
	{
		newpath = ft_strjoin(paths[i], "/");
		if (!newpath)
			exit(1);
		fullpath = ft_strjoin(newpath, cmd);
		if (access(fullpath, F_OK) == 0 && access(fullpath, X_OK) == 0)
		{
			free(newpath);
			return (fullpath);
		}
		free(newpath);
		free(fullpath);
		i++;
	}
	newpath = ft_strjoin(paths[0], "/");
	fullpath = ft_strjoin(newpath, cmd);
	free(newpath);
	return (fullpath);
}

char	**ft_checkenv(char *env[])
{
	int		i;
	char	*defpath;
	char	**paths;
	char	*envline;

	i = 0;
	paths = NULL;
	defpath = "/usr/bin/:/bin/";
	while (env[i])
	{
		envline = ft_strnstr(env[i], "PATH=", 5);
		if (envline != NULL)
			paths = ft_split(&envline[5], ':');
		i++;
	}
	if (paths == NULL)
		paths = ft_split(defpath, ':');
	return (paths);
}

char		*ft_checkpath(char *env[], char *cmd)
{
	char	**paths;
	char	*fullpath;
	char	*cmd_cpy;

	if (!cmd)
		cmd = "";
	if (ft_strchr(cmd, '/'))
	{
		cmd_cpy = ft_strdup(cmd);
		return (cmd_cpy);
	}
	paths = ft_checkenv(env);
	fullpath = ft_checkexe(paths, cmd);
	ft_free(paths);
	return (fullpath);
}
