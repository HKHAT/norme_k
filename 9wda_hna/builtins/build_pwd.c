/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:03:14 by yozainan          #+#    #+#             */
/*   Updated: 2024/07/28 20:09:48 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	build_pwd(t_data *data)
{
	char	pwd[PATH_MAX];
	char	*oldpwd;
	int		fd;

	fd = data->cmd->fdout;
	if (getcwd(pwd, PATH_MAX))
	{
		ft_putendl_fd(pwd, fd);
		data->exit_status = EXIT_SUCCESS;
	}
	else
	{
		oldpwd = ft_getenv(data->env_list, "PWD");
		if (oldpwd)
		{
			ft_putendl_fd(oldpwd, fd);
			data->exit_status = EXIT_SUCCESS;
		}
		else
		{
			ft_putendl_fd(PWD_ERROR_MSG, fd);
			data->exit_status = EXIT_FAILURE;
		}
	}
}
