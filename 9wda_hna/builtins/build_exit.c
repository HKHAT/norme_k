/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:42:06 by yozainan          #+#    #+#             */
/*   Updated: 2024/08/08 15:12:29 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_number(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	validate_exit_argument(char *arg, long long *rs)
{
	*rs = ft_atoll(arg);
	if (!check_number(arg) || *rs == LLONG_MAX || *rs == LLONG_MIN)
	{
		ft_putstr_fd("minishell: exit : ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		g_data.exit_status = 2;
		return (0);
	}
	return (1);
}

void	build_exit(char **av)
{
	long long	rs;

	g_data.exit_status = 0;
	if (!g_data.is_pipeline)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (av[1])
	{
		if (!validate_exit_argument(av[1], &rs))
			exit(g_data.exit_status);
		g_data.exit_status = rs % 256;
		if (g_data.exit_status < 0)
			g_data.exit_status = 256 + g_data.exit_status;
		if (av[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n",
				STDERR_FILENO);
			g_data.exit_status = 1;
			exit(g_data.exit_status);
		}
	}
	exit(g_data.exit_status);
}
