/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:36:21 by yozainan          #+#    #+#             */
/*   Updated: 2024/08/04 04:13:41 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_ambiguous_unexpected_tokens(Token *tokens, int i)
{
	if (((tokens[i].type == TOKEN_HERE_DOC && tokens[i + 1].type != TOKEN_WORD)
			|| (tokens[i].type == TOKEN_REDIRECT_IN && tokens[i
				+ 1].type != TOKEN_WORD)
			|| (tokens[i].type == TOKEN_REDIRECT_OUT && tokens[i
				+ 1].type != TOKEN_WORD) || (tokens[i].type == TOKEN_APPEND_OUT
				&& tokens[i + 1].type != TOKEN_WORD)) && (tokens[i
			+ 1].type != TOKEN_AMBIGUOUS))
	{
		return (printf("Syntax error: near unexpected token 2 '%s'\n",
				tokens[i].value), 1);
	}
	return (0);
}

int check_syn(Token *tokens, int nb_tokens,int i)
{
		if (check_ambiguous_unexpected_tokens(tokens, i))
			return (1);
		if (is_double_token_error(tokens, i))
			return (1);
		if (is_initial_token_error(tokens, i))
			return (1);
		if (is_final_token_error(tokens, i, nb_tokens))
			return (1);
		if (is_invalid_sequence(tokens, i))
			return (1);
	return 0;
}

int	check_syntaxe(Token *tokens, int nb_tokens)
{
	int	i;

	i = 0;
	while (i < nb_tokens && tokens[i].type != TOKEN_END)
	{
		if (tokens[i].type == NOT_DEFINE)
			return (1);
		if (tokens[i].type == TOKEN_OR || tokens[i].type == TOKEN_AND
			|| tokens[i].type == TOKEN_LPR || tokens[i].type == TOKEN_BACKGROUND
			|| tokens[i].type == TOKEN_RPR)
			return (printf("Syntax error: undefined token '%s'\n",
					tokens[i].value), 1);
		if (i && tokens[i].type == TOKEN_PIPE && tokens[i
			- 1].type != TOKEN_AMBIGUOUS && tokens[i + 1].type == TOKEN_END)
			return (printf("Syntax error: undefined token 111 '%s'\n",
					tokens[i].value), 1);
		if(check_syn(tokens,nb_tokens,i))
			return 1;
		i++;
	}
	return (0);
}

bool	is_double_token_error(Token *tokens, int i)
{
	if (tokens[i].type == tokens[i + 1].type && tokens[i].type != TOKEN_WORD
		&& tokens[i].type != TOKEN_END)
	{
		return (printf("Syntax error: unexpected token '%s'\n",
				tokens[i].value), true);
	}
	return (false);
}

void add_cmd_to_arg(Command *head)
{
	Command *temp;
	temp = head;
	while (temp)
	{
		temp->av = ft_list_to_char(temp->cmd_lst, \
		ft_lst_size(temp->cmd_lst));
		temp = temp->next;
	}
}

Command *parse(Token *tokens)
{
	Command *head;
	t_cmd *cmd_head;
	Command *current;
	t_value value;

	value.flag = 0;
	value.i = 0;
	head = NULL;
	cmd_head = NULL;
	current = create_command();
	if (!current)
		return NULL;
	while (tokens[value.i].type != TOKEN_END)
	{
		process_token(tokens, &value, &current, &head, &cmd_head);
	}
	if (current && (ft_lst_size(current->cmd_lst) > 0 || value.flag > 0))
	{
		add_cmd(&current->cmd_lst, cmd_head);
		add_command_to_list(&head, current);
	}
	add_cmd_to_arg(head);
	return head;
}

int	ft_size(char **argv)
{
	int	i;

	if (argv == NULL)
		return 0;
	i = 0;
	while (argv[i] != NULL)
		i++;
	return i;
}
