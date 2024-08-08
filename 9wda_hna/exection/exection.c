/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exection.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:42:06 by yozainan          #+#    #+#             */
/*   Updated: 2024/08/08 14:59:20 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_sigint(int sig)
{
    (void)sig;
    ft_putstr_fd("\n", STDOUT_FILENO);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    g_data.exit_status = 130;
}

void herd_sig(int sig)
{
    if (sig == SIGINT)
    {
        write(1, "\n", 1);
        exit(1);
    }
}

t_data *get_global_data(void)
{
    g_data.exit_status = 0;
    return (&g_data);
}

int ft_strlnode(Command *cmd)
{
    int i;

    i = 0;
    while (cmd)
    {
        i++;
        cmd = cmd->next;
    }
    return (i);
}

void init_execution(t_data *data, int *status)
{
    if (data->size_cmds == 1)
        singel_cmd(data, status);
    else
    {
        while (data->cmd != NULL)
        {
            if (data->cmd->redir_erros == -1)
                data->cmd = data->cmd->next;
            multiple_cmd(data, status);
            data->cmd = data->cmd->next;
        }
    }
}

void check_invalid_redirections(t_data *data)
{
    Command *current_cmd;
    Redirection *redir;

    current_cmd = data->cmd;
    while (current_cmd != NULL)
    {
        if (current_cmd->type == TOKEN_AMBIGUOUS)
        {
            ft_putstr_fd("minishell: ambiguous redirect\n", 2);
            data->cmd->dup = 1;
            return ;
        }
        redir = current_cmd->redirection;
        while (redir != NULL)
        {
            if (!ft_strcmp(redir->filename, "") || ((redir->type == TOKEN_REDIRECT_IN) && access(redir->filename, R_OK) == -1))
            {
                ft_putstr_fd("minishell: ", 2);
                ft_putstr_fd(data->cmd->av[0], 2);
                ft_putstr_fd(": No such file or directory\n", 2);
                data->cmd->dup = 1;
                break;
            }
            redir = redir->next;
        }
        current_cmd = current_cmd->next;
    }
}

void execution(t_data *data)
{
    int status;
    Redirection *redir;

    status = 0;
    fill_cmd(data);
    // print_command_structure(data->cmd);
    Command *current_cmd = data->cmd;
    while (current_cmd != NULL)
    {
        redir = current_cmd->heredoc;
        while (redir != NULL)
        {
            handle_heredoc(data, redir);
            redir = redir->next;
        }
        current_cmd = current_cmd->next;
    }
    if (data->her_erros)
            return ;
    check_invalid_redirections(data);
    if (data->cmd->dup != 1)
        open_check_redirections(data);
    while (data->cmd && data->cmd->redir_erros == -1)
        data->cmd = data->cmd->next;
    if (!data->cmd)
        return;
    data->is_pipeline = (data->size_cmds > 1);
    init_execution(data, &status);
    wating_processes(data, &status);
}
