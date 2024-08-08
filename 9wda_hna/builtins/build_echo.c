/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:42:06 by yozainan          #+#    #+#             */
/*   Updated: 2024/08/08 12:18:03 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_av(char **av, int n, int fd)
{
	int	i;

	i = 0;
	while (av[i])
	{
		ft_putstr_fd(av[i], fd);
		if (av[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (i == 0 || n)
		ft_putstr_fd("\n", fd);
}

int	check_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] != 'n')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	check_option(char **av, int fd)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (av[i] && av[i][0] == '-' && !check_n(av[i] + 1))
	{
		n_flag = 1;
		i++;
	}
	if (!av[i])
		return ;
	print_av(av + i, !n_flag, fd);
}

void	build_echo(t_data *data)
{
	int	fd;

	fd = data->cmd->fdout;
	if (data->cmd->av[1] == NULL)
		ft_putstr_fd("\n", fd);
	else if (data->cmd->av[1][0] == '-')
		check_option(data->cmd->av, fd);
	else
		print_av(data->cmd->av + 1, 1, fd);
}
