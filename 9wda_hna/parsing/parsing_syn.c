/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 04:14:04 by elchakir          #+#    #+#             */
/*   Updated: 2024/08/04 06:18:01 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


bool	is_initial_token_error(Token *tokens, int i)
{
	if (i == 0 && (tokens[i].type == TOKEN_AND || tokens[i].type == TOKEN_OR
			|| tokens[i].type == TOKEN_PIPE
			|| tokens[i].type == TOKEN_BACKGROUND))
	{
		return (printf("Syntax error: unexpected token '%s'\n",
				tokens[i].value), true);
	}
	return (false);
}

bool	is_final_token_error(Token *tokens, int i, int nb_tokens)
{
	if (i == nb_tokens - 1 && (tokens[i].type == TOKEN_AND
			|| tokens[i].type == TOKEN_OR || tokens[i].type == TOKEN_PIPE
			|| tokens[i].type == TOKEN_BACKGROUND))
	{
		return (printf("Syntax error: unexpected token '%s'\n",
				tokens[i].value), true);
	}
	return (false);
}

bool	is_invalid_sequence(Token *tokens, int i)
{
	if ((tokens[i].type == TOKEN_AND && tokens[i + 1].type == TOKEN_AND)
		|| (tokens[i].type == TOKEN_OR && tokens[i + 1].type == TOKEN_OR)
		|| (tokens[i].type == TOKEN_BACKGROUND && tokens[i
			+ 1].type == TOKEN_BACKGROUND))
	{
		return printf("Syntax error: unexpected token '%s'\n", tokens[i].value),
			true;
	}
	return false;
}

bool	is_operator(Token token)
{
	return token.type == TOKEN_PIPE || token.type == TOKEN_AND
		|| token.type == TOKEN_OR;
}

void process_token(Token *tokens, t_value *value, Command **current,
				   Command **head, t_cmd **cmd_head)
{
	if (tokens[value->i].type == TOKEN_WORD)
	{
		handle_word(tokens, &value->i, current);
	}
	else if (is_operator(tokens[value->i]))
		process_operator(tokens, &value->i, current, head, cmd_head);
	else if (is_redirection(tokens[value->i]) && tokens[value->i + 1].type != TOKEN_AMBIGUOUS && tokens[value->i + 1].type != TOKEN_HASHTAG)
	{
		handle_redirection(tokens, &value->i, current);
		value->flag++;
	}
	else if(tokens[value->i].type == TOKEN_HASHTAG)
		(*current)->type = TOKEN_HASHTAG;
	else if(is_redirection(tokens[value->i])&& tokens[value->i + 1].type == TOKEN_HASHTAG)
		(*current)->type = TOKEN_HASHTAG;
	else if (is_redirection(tokens[value->i]) && tokens[value->i + 1].type == TOKEN_AMBIGUOUS)
		(*current)->type = TOKEN_AMBIGUOUS;
	else if (is_parenthesis(tokens, value->i))
		value->flag++;
	else if (tokens[value->i].type != TOKEN_AMBIGUOUS && tokens[value->i].type != TOKEN_HASHTAG)
	{
		handle_syntax_error();
	}
	value->i++;
}