/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:20:21 by elchakir          #+#    #+#             */
/*   Updated: 2024/08/04 06:15:20 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_command(Command *cmd)
{
	cmd->cmd_lst = NULL;
	cmd->redirection = NULL;
	cmd->heredoc = NULL;
	cmd->next = NULL;
}

Command* create_command() 
{
    Command *cmd = (Command *)malloc(sizeof(Command));
    if (!cmd) return NULL;
    init_command(cmd);
    return cmd;
}

void add_command_to_list(Command **head, Command *current) 
{
    if (*head == NULL) 
        *head = current;
    else 
    {
        Command *last = *head;
        while (last->next != NULL)
            last = last->next;
        last->next = current;
    }
}

void	add_cmd(t_cmd **head,t_cmd *cmmd)
{
	t_cmd	*last;

	if (*head == NULL)
		*head = cmmd;
	else
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = cmmd;
	}
}

void	handle_word(Token *tokens, int *i, Command **current)
{
	t_cmd *new_cmd;
	new_cmd = malloc(sizeof(t_cmd));
	if (*current == NULL)
	{
		*current = create_command();
	}
	if(tokens[*i + 1].type == TOKEN_AMBIGUOUS
		||tokens[*i + 1].type == TOKEN_HASHTAG)
	{
		(*current)->type = tokens[*i + 1].type;
	}
	new_cmd->value = tokens[*i].value;
	new_cmd->next = NULL;
	add_cmd(&(*current)->cmd_lst, new_cmd);
}
