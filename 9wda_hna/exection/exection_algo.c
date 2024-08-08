/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exection_algo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:42:06 by yozainan          #+#    #+#             */
/*   Updated: 2024/08/08 15:06:43 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_dup_in(t_data *data)
{
	if (dup2(data->cmd->fdin, STDIN_FILENO) == -1)
	{
		perror("dup2 single_cmd fdin");
		exit(EXIT_FAILURE);
	}
	close(data->cmd->fdin);
}

void ft_dup_out(t_data *data, int i)
{
	if (i == 1)
	{
		data->cmd->fdin = 0;
		data->cmd->fdout = 1;
	}
	else
	{
		if (dup2(data->cmd->fdout, STDOUT_FILENO) == -1)
		{
			perror("dup2 single_cmd fdout");
			exit(EXIT_FAILURE);
		}
		close(data->cmd->fdout);
	}
}

void handle_child_process(t_data *data, int pipe_fd[2])
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (data->cmd->fdin >= 3)
		ft_dup_in(data);
	else if (data->fd[0] >= 3)
	{
		dup2(data->fd[0], STDIN_FILENO);
		close(data->fd[0]);
	}
	if (data->cmd->fdout >= 3)
		ft_dup_out(data, 0);
	else if (data->cmd->next)
		dup2(pipe_fd[1], STDOUT_FILENO);
	if (pipe_fd[1] >= 3)
		close(pipe_fd[1]);
	if (pipe_fd[0] >= 3)
		close(pipe_fd[0]);
	ft_dup_out(data, 1);
	if (data->cmd->dup == 1)
	{
		data->cmd->dup = 0;
		exit(1);
	}
	if (check_is_builtin(*data))
		execute_builtin(data);
	else
		run_execution(data);
	exit(data->exit_status);
}

void singel_cmd(t_data *data, int *status)
{
	if (check_is_builtin(*data) == 1)
		run_builtin(data, status);
	else
	{
		data->pid = fork();
		if (data->pid == -1)
		{
			perror("fork");
			*status = 1;
			return;
		}
		else if (data->pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (data->cmd->fdin > 2)
				ft_dup_in(data);
			if (data->cmd->fdout != STDOUT_FILENO)
				ft_dup_out(data, 0);
			run_execution(data);
			exit(EXIT_SUCCESS);
		}
	}
}

void multiple_cmd(t_data *data, int *status)
{
    int	pipe_fd[2];

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
    if (data->cmd->next && pipe(pipe_fd) == -1)
    {
        perror("pipe");
        *status = 1;
        return;
    }
    data->pid = fork();
    if (data->pid == 0)
        handle_child_process(data, pipe_fd);
    else
    {
        if (pipe_fd[1] >= 3)
            close(pipe_fd[1]);
        if (data->fd[0] >= 3)
            close(data->fd[0]);
        data->fd[0] = pipe_fd[0];
    }
}
