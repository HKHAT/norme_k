/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exection_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:42:06 by yozainan          #+#    #+#             */
/*   Updated: 2024/08/08 13:29:00 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*build_executable_path(char *path, char *cmd)
{
	char	*tmp_path;
	char	*exec_path;

	tmp_path = ft_strjoin(path, "/");
	exec_path = ft_strjoin(tmp_path, cmd);
	free(tmp_path);
	if (access(exec_path, F_OK | X_OK) == 0)
		return (exec_path);
	free(exec_path);
	return (NULL);
}

char	*check_cmd(char *cmd)
{
	if (access(cmd, F_OK) == -1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory ==== \n", 2);
		exit(127);
	}
	else if (access(cmd, X_OK) == -1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
	return (cmd);
}

char	*find_path(char *cmd, char **env)
{
	char	**path;
	char	*exec_path;
	int		i;

	if (*cmd == '\0' || !env)
		return NULL;
	i = 0;
	if (ft_strchr(cmd, '/'))
		return (check_cmd(cmd));
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			break ;
		i++;
	}
	if (!env[i])
		return NULL;
	path = ft_split(env[i] + 5, ':');
	if (!path)
		return NULL;
	i = 0;
	while (path[i])
	{
		exec_path = build_executable_path(path[i], cmd);
		if (exec_path != NULL)
			return (clear_tab(path), exec_path);
		i++;
	}
	return (clear_tab(path), NULL);
}
