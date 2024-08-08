/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exection_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:42:06 by yozainan          #+#    #+#             */
/*   Updated: 2024/08/08 12:18:03 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wating_processes(t_data *data, int *status)
{
	pid_t	pid;
	int		wstatus;
	int		i;

	i = 0;
	waitpid(data->pid, status, 0);
	while (++i < data->size_cmds)
	{
		pid = wait(&wstatus);
		if (pid == -1)
			continue ;
	}
	if (WIFEXITED(*status))
		data->exit_status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
	{
		if (WTERMSIG(*status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		else if (WTERMSIG(*status) == SIGINT)
			ft_putstr_fd("\n", 2);
		data->exit_status = 128 + WTERMSIG(*status);
	}
}

void	handle_exec_error(char *cmd)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putchar_fd('\n', 2);
	exit(127);
}

void	handle_is_directory(char *exec_path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(exec_path, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	free(exec_path);
	exit(126);
}

void	run_execution(t_data *data)
{
	char		*exec_path;
	struct stat	path_stat;

	if (!data->cmd->av[0])
        return ;
	data->env = list_to_char(data->env_list);
	exec_path = find_path(data->cmd->av[0], data->env);
	if (!exec_path)
		handle_exec_error(data->cmd->av[0]);
	if (stat(exec_path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		handle_is_directory(exec_path);
	execve(exec_path, data->cmd->av, data->env);
	perror("minishell");
	exit(127);
}
