/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:20:21 by elchakir          #+#    #+#             */
/*   Updated: 2024/08/04 03:19:17 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_strncpy(char *dest, const char *src, int n)
{
	while (n--)
		*dest++ = *src++;
	*dest = '\0';
}

void process_operator(Token *tokens, int *i, Command **current, Command **head, t_cmd **cmd_head)
{
	add_cmd(&(*current)->cmd_lst, *cmd_head);
	add_command_to_list(head, *current);
	*current = create_command();
	if (!*current)
		return;
	(*current)->type = tokens[*i].type;
}


bool	is_redirection(Token token)
{
	return token.type == TOKEN_REDIRECT_IN || token.type == TOKEN_REDIRECT_OUT
		|| token.type == TOKEN_APPEND_OUT || token.type == TOKEN_HERE_DOC||token.type == TOKEN_HERE_DOC_NO;
}

bool	is_parenthesis(Token *tokens, int i)
{
	return (tokens[i].type == TOKEN_LPR && tokens[i + 1].type == TOKEN_WORD)
		|| (tokens[i].type == TOKEN_RPR && tokens[i - 1].type == TOKEN_WORD
		&& i > 1);
}

void	handle_syntax_error(void)
{
	write(2, "minishell: syntax error near unexpected token newline\n", 55);
}