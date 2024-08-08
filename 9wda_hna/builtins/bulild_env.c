/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulild_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:42:06 by yozainan          #+#    #+#             */
/*   Updated: 2024/08/08 12:18:03 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_erros(t_data *data, int fd)
{
	ft_putstr_fd("env: ‘", fd);
	ft_putstr_fd(data->cmd->av[1], fd);
	ft_putstr_fd("’: No such file or directory\n", fd);
	data->exit_status = EXIT_FAILURE;
}

void	build_env(t_data *data)
{
	t_env_node	*curr;
	int			fd;

	fd = data->cmd->fdout;
	curr = data->env_list;
	if (data->ac == 1)
	{
		while (curr)
		{
			if (curr->value)
			{
				ft_putstr_fd(curr->name, fd);
				ft_putstr_fd("=", fd);
				ft_putstr_fd(curr->value, fd);
				ft_putstr_fd("\n", fd);
			}
			curr = curr->next;
		}
	}
	else
		print_erros(data, fd);
}
