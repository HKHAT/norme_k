/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 03:30:57 by elchakir          #+#    #+#             */
/*   Updated: 2024/08/04 06:15:11 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void ft_buffer_split(Token *tokens, int *nb, const char *str)
{
	char *token_value;
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (!ft_isspace((unsigned char)str[i]))
		{
			token_value = alloc_token(str, &j, i);
			if (token_value)
				add_token(tokens, nb, TOKEN_WORD, token_value);
			i = j;
		}
		else
			i++;
	}
}

int check_space(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
			return (1);
		i++;
	}
	return (0);
}

int handel_quotes(const char **p, QuoteWordParserState *state)
{
	if (**p == '\\' && *(*p + 1) != '\0')
	{
		state->buffer[state->buffer_index++] = *(*p + 1);
		(*p) += 2;
		return (1);
	}
	else if ((**p == '"' || **p == '\'') && (state->in_quotes == 0 || **p == state->quote_char))
	{
		state->quote = 1;
		if (**p == '"')
		{
			state->double_quotes = 1;
		}
		handle_quotes_and_wordsv2(p, &state);
		(*p)++;
		return (1);
	}
	return (0);
}


int dollar(const char **p, QuoteWordParserState *state)
{
	char *pid_str;
	int i;

	i = 0;
	if (state->start[0] == '$')
	{
		pid_str = ft_itoa(g_data.pid);
		while (pid_str[i])
			state->buffer[state->buffer_index++] = pid_str[i++];
		(*p)++;
		return (free(pid_str), 1);
	}
	else if (state->start[0] == '?')
	{
		state->expanded_value = ft_itoa(g_data.exit_status);
		while (state->expanded_value[i])
			state->buffer[state->buffer_index++] = state->expanded_value[i++];
		free(state->expanded_value);
		state->expanded_value = NULL;
		g_data.exit_status = 0;
		(*p)++;
		state->expandit = 1;
	}
	return (0);
}

int handel_dollar_expand(const char **p, QuoteWordParserState *state)
{
	if (dollar(p, state))
		return (1);
	return (0);
}