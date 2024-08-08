/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:36:21 by yozainan          #+#    #+#             */
/*   Updated: 2024/08/04 04:15:15 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_redirection(Redirection *redir)
{
	Redirection	*next;

	while (redir != NULL)
	{
		next = redir->next;
		if (redir->filename != NULL)
			free(redir->filename);
		free(redir);
		redir = next;
	}
}

void	free_all_v2(Command *current)
{
	if (current->redirection != NULL)
		free_redirection(current->redirection);
	if (current->heredoc != NULL)
		free_redirection(current->heredoc);
}

void	free_all_resources(Command *head)
{
	Command	*current;
	Command	*next;
	int		i;

	current = head;
	if (head == NULL)
		return ;
	while (current != NULL)
	{
		next = current->next;
		if (current->av != NULL)
		{
			i = 0;
            while (current->av[i] != NULL)
			{
                if (current->av[i] != NULL)
                    free(current->av[i]);
				i++;
			}
			if (current->av != NULL)
				free(current->av);
		}
		free_all_v2(current);
		if (current != NULL)
			free(current);
		current = next;
	}
}

int end_dollar(const char **p, QuoteWordParserState *state)
{
	if (handel_dollar_expand(p, state))
		return (1);
	return (0);
}

int check_ambiguous(Token *tokens, int *num_tokens, QuoteWordParserState *state)
{
	if (is_ambiguous(state->expanded_value) && *num_tokens > 0 
	&& (tokens[*num_tokens - 1].type == TOKEN_REDIRECT_OUT 
	||tokens[*num_tokens - 1].type == TOKEN_APPEND_OUT 
	|| tokens[*num_tokens - 1].type == TOKEN_REDIRECT_IN))
	{
		free(state->expanded_value);
		add_token(tokens, num_tokens, TOKEN_AMBIGUOUS, "?");
		return (1);
	}
	return (0);
}
