/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_mini.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:31:07 by yozainan          #+#    #+#             */
/*   Updated: 2024/07/13 14:45:30 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_env_list(t_env_node **env_list, t_env_node *new_node)
{
	t_env_node	*current;

	if (!*env_list)
	{
		*env_list = new_node;
		return ;
	}
	current = *env_list;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

t_env_node	*fill_env(char *env_str)
{
	t_env_node	*new_node;
	char		*delimiter_pos;

	new_node = (t_env_node *)malloc(sizeof(t_env_node));
	if (!new_node)
		return (NULL);
	delimiter_pos = ft_strrch_finder(env_str, '=');
	if (!delimiter_pos)
	{
		new_node->name = ft_strdup(env_str);
		new_node->value = NULL;
	}
	else
	{
		new_node->name = ft_strndup(env_str, delimiter_pos - env_str);
		new_node->value = ft_strdup(delimiter_pos + 1);
	}
	new_node->next = NULL;
	if (!new_node->name || (delimiter_pos && !new_node->value))
		return (free(new_node->name), free(new_node->value), free(new_node),
			NULL);
	return (new_node);
}

t_env_node	*create_env_list(char **s_env)
{
	t_env_node	*env_list;
	t_env_node	*new_node;
	int			i;
	t_env_node	*temp;

	env_list = NULL;
	i = 0;
	while (s_env[i])
	{
		new_node = fill_env(s_env[i]);
		if (!new_node)
		{
			while (env_list)
			{
				temp = env_list;
				env_list = env_list->next;
				free(temp->name);
				free(temp->value);
				free(temp);
			}
			return (NULL);
		}
		add_env_list(&env_list, new_node);
		i++;
	}
	return (env_list);
}

void	ft_init_minishell(int ac, char **av, char **env, t_data *data)
{
	(void)env;
	data->ac = ac;
	data->av = av;
	data->exit_status = 0;
}

void	free_env_list(t_env_node *env_list)
{
	while (env_list)
	{
		t_env_node *tmp = env_list;
		env_list = env_list->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}