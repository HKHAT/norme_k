/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:37:48 by yozainan          #+#    #+#             */
/*   Updated: 2024/08/02 21:22:12 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_or_add_env(t_env_node **env_list, char *name, char *value)
{
	t_env_node	*current;
	t_env_node	*new_node;

	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	new_node = malloc(sizeof(t_env_node));
	if (!new_node)
		return ;
	new_node->name = ft_strdup(name);
	new_node->value = ft_strdup(value);
	new_node->next = *env_list;
	*env_list = new_node;
}

void	ft_swap_env(t_env_node *a, t_env_node *b)
{
	char	*tmp_name;
	char	*tmp_value;

	tmp_name = a->name;
	tmp_value = a->value;
	a->name = b->name;
	a->value = b->value;
	b->name = tmp_name;
	b->value = tmp_value;
}

void	handle_new_env(t_env_node **env_list, char *arg)
{
	t_env_node	*current;
	char		*name;
	char		*value;

	name = ft_strdup(arg);
	current = find_env(*env_list, name);
	if (current)
	{
		free(name);
		return ;
	}
	value = NULL;
	update_or_add_env(env_list, name, value);
}

void	append_to_existing_env(t_env_node *current, char *name, char *value)
{
	char	*new_value;

	new_value = ft_strjoin(current->value, value);
	free(current->value);
	current->value = new_value;
	free(name);
	free(value);
}

void	existing_env(t_env_node **env_list, char *name, char *value)
{
	t_env_node	*current;

	current = find_env(*env_list, name);
	if (current)
		append_to_existing_env(current, name, value);
	else
		update_or_add_env(env_list, name, value);
}
