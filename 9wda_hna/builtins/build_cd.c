/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:03:14 by yozainan          #+#    #+#             */
/*   Updated: 2024/08/08 12:18:03 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_directory_permissions(char *path, t_data *data)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
	{
		perror("minishell: cd");
		data->exit_status = 1;
		return (0);
	}
	if (!S_ISDIR(statbuf.st_mode))
	{
		ft_putstr_fd("minishell: cd: not a directory: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		data->exit_status = 1;
		return (0);
	}
	else if (access(path, X_OK) != 0)
	{
		ft_putstr_fd("minishell: cd: permission denied: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		data->exit_status = 1;
		return (0);
	}
	return (1);
}

int	validation_home(t_env_node *env)
{
	while (env)
	{
		if (!ft_strncmp(env->name, "HOME", 4))
		{
			if (env->name[4] == '=' || env->name[4] == '\0')
				return (1);
		}
		env = env->next;
	}
	return (0);
}

void	go_home(t_data *data)
{
	char	*path;
	int		i;

	if (!validation_home(data->env_list))
	{
		ft_putstr_fd("minishell: cd : HOME not set\n", 2);
		data->exit_status = EXIT_FAILURE;
		return ;
	}
	else
	{
		update_env_var(&data->env_list, "OLDPWD",
			ft_strdup(ft_getenv(data->env_list, "PWD")));
		path = ft_getenv(data->env_list, "HOME");
		if (check_directory_permissions(path, data))
		{
			i = chdir(path);
			if (i)
				printf("minishell: cd: %s: No such file or directory\n", path);
			set_pwd(data->env_list);
		}
		else
			data->exit_status = EXIT_FAILURE;
	}
}

void	change_directory(t_data *data, const char *path)
{
	char	new_cwd[PATH_MAX];

	if (check_directory_permissions((char *)path, data))
	{
		if (chdir(path) == 0)
		{
			update_env_var(&data->env_list, "OLDPWD",
				ft_strdup(ft_getenv(data->env_list, "PWD")));
			if (!getcwd(new_cwd, PATH_MAX))
			{
				perror("minishell: getcwd:");
				data->exit_status = EXIT_FAILURE;
				return ;
			}
			update_env_var(&data->env_list, "PWD", new_cwd);
		}
		else
		{
			printf("minishell: cd: %s: No such file or directory\n", path);
			data->exit_status = EXIT_FAILURE;
		}
	}
	else
		data->exit_status = EXIT_FAILURE;
}

void	build_cd(t_data *data)
{
	char	*oldcwd;

	oldcwd = getcwd(NULL, PATH_MAX);
	if (!oldcwd)
		oldcwd = ft_strdup(ft_getenv(data->env_list, "PWD"));
	if (data->ac > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		data->exit_status = EXIT_FAILURE;
		free(oldcwd);
		return ;
	}
	if (!data->cmd->av[1] || !ft_strcmp(data->cmd->av[1], "~"))
		go_home(data);
	else if (!ft_strcmp(data->cmd->av[1], "-"))
		swap_pwd_oldpwd(data);
	else
		change_directory(data, data->cmd->av[1]);
	free(oldcwd);
}
