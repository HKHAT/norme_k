/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 03:22:19 by elchakir          #+#    #+#             */
/*   Updated: 2024/08/04 03:25:48 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_here_doc_expand(const char **p)
{
	const char *str;
	str = (*p + 2);
	while(ft_isspace(*str))
		str++;
	if((*str) == '"' || (*str) == '\'')
		return 1;
	return 0;
}
void doc_or_in(const char **p, TokenType *type, char *special)
{
	if (*(*p + 1) == '<')
	{
		special[0] = '<';
		special[1] = '<';
		special[2] = '\0';

		if (check_here_doc_expand(p))
			*type = TOKEN_HERE_DOC_NO;
		else
			*type = TOKEN_HERE_DOC;
		(*p)++;
	}
	else if (**p == '<' && *(*p + 1) != '<')
	{
		*type = TOKEN_REDIRECT_IN;
	}
	else if (**p == '<' && *(*p + 1) == '#')
		*type = TOKEN_HASHTAG;
}

void handel_q(const char **p, TokenType type, Token *tokens, int *num_tokens)
{
	char *sp;

	if (**p == '(')
	{
		type = TOKEN_LPR;
		sp = " ( ";
		(*p)++;
		add_token(tokens, num_tokens, type, sp);
		return;
	}
	else if (**p == ')')
	{
		type = TOKEN_RPR;
		sp = " ) ";
		(*p)++;
		add_token(tokens, num_tokens, type, sp);
		return;
	}
}

void handle_special_characters(const char **p, Token *tokens,
							   int *num_tokens)
{
	TokenType type;
	char special[4];

	type = TOKEN_WORD;
	if (**p == '|' || **p == '<' || **p == '>' || **p == '&')
	{
		special[0] = **p;
		special[1] = '\0';
		type = TOKEN_WORD;
		if (**p == '|' && *(*p + 1) != '|')
			type = TOKEN_PIPE;
		else if (**p == '|' && *(*p + 1) == '|')
			type = TOKEN_OR;
		else if (**p == '&')
			hanv3(p, special, &type);
		else if (**p == '<')
			doc_or_in(p, &type, special);
		else if (**p == '>')
			handle_v2(p, special, &type);
		add_token(tokens, num_tokens, type, special);
		(*p)++;
		return;
	}
	else
		handel_q(p, type, tokens, num_tokens);
}

QuoteWordParserState init_lexer(t_env_node *env)
{
	QuoteWordParserState state;
	state.in_quotes = 0;
	state.quote_char = '\0';
	state.status = true;
	state.buffer_index = 0;
	state.expanded_value = NULL;
	state.double_quotes = 0;
	state.expandit = 0;
	state.buffer_index = 0;
	state.flag = 0;
	state.start = NULL;
	state.quote = 0;
	state.env = env;
	ft_memset(state.buffer, 0, sizeof(state.buffer));
	return state;
}