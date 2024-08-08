/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 03:26:45 by elchakir          #+#    #+#             */
/*   Updated: 2024/08/04 04:26:43 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int splited(Token *tokens, int *num_tokens,
		   QuoteWordParserState *state)
{
	int i;
	i = 0;
	if(state->double_quotes || check_space(state->expanded_value) == 0)
		{
				while (state->expanded_value[i] && state->start[0] != '?')
					state->buffer[state->buffer_index++] = state->expanded_value[i++];
				state->buffer[state->buffer_index] = '\0';
				free(state->expanded_value);
		}
		else if (!state->double_quotes)
		{
				ft_buffer_split(tokens, num_tokens, state->expanded_value);
				return (free(state->expanded_value), 1);
		}
		return 0;
}


int add_to(const char **p, Token *tokens, int *num_tokens,
		   QuoteWordParserState *state)
{
	int i;

	i = 0;
	while (ft_isalnum(**p) || **p == '_')
		(*p)++;
	if (*p > state->start)
	{
		state->expanded_value = expand_variable(state->start, *p - state->start,
												state->env);
		if (check_ambiguous(tokens, num_tokens, state))
			return (1);
		else if (state->expandit == 0)
		{
			if (state->double_quotes || check_space(state->expanded_value) == 0)
			{
				while (state->expanded_value[i] && state->start[0] != '?')
					state->buffer[state->buffer_index++] = state->expanded_value[i++];
				state->buffer[state->buffer_index] = '\0';
				free(state->expanded_value);
			}
			else if (!state->double_quotes)
			{
				ft_buffer_split(tokens, num_tokens, state->expanded_value);
				return (free(state->expanded_value), 1);
			}
		}
	}
	else
		state->buffer[state->buffer_index++] = '$';
	return 0;
}

void handle_quotes_and_words(const char **p, Token *tokens, int *num_tokens,
							 QuoteWordParserState *state)
{
	state->buffer_index = 0;
	while (ft_isspace(**p) && !state->in_quotes)
		(*p)++;
    while (**p != '\0' && (state->in_quotes || (!ft_isspace(**p) && !ft_strchr("<>|&()",**p))))
	{
		if (handel_quotes(p, state) == 1)
			continue;
		if (**p == '$' && *(*p + 1) != '\0' && state->quote_char != '\'')
		{
			(*p)++;
			state->start = *p;
			if (end_dollar(p, state))
				continue;
			if (add_to(p, tokens, num_tokens, state))
				return;
		}
		else
			state->buffer[state->buffer_index++] = *(*p)++;
	}
	if (state->buffer_index == 0 && state->in_quotes)
	    state->buffer[0] = '\0';
	state->buffer[state->buffer_index] = '\0';

	if ((state->buffer_index > 0 && state->flag == 0)||(state->buffer_index == 0 && !state->in_quotes && state->quote))
		// Only add token if buffer is not empty
		add_token(tokens, num_tokens, TOKEN_WORD, state->buffer);
}

void hanv3(const char **p, char *special, TokenType *type)
{
	if (**p == '&')
	{
		if (*(*p + 1) == '&')
		{
			*type = TOKEN_AND;
			special[0] = '&';
			special[1] = '&';
			special[2] = '\0';
			(*p)++;
		}
		else
		{
			special[0] = '&';
			special[1] = '\0';
			*type = TOKEN_BACKGROUND;
		}
	}
}

void handle_v2(const char **p, char *special, TokenType *type)
{
	if (**p == '>')
	{
		if (*(*p + 1) == '>')
		{
			special[0] = '>';
			*type = TOKEN_APPEND_OUT;
			(*p)++;
		}
		else if (**p == '>' && *(*p + 1) != '>')
			*type = TOKEN_REDIRECT_OUT;
		else if (**p == '>' && *(*p + 1) == '#')
			*type = TOKEN_HASHTAG;
	}
}
