/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exection_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:42:06 by yozainan          #+#    #+#             */
/*   Updated: 2024/08/07 06:53:41 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_cmd(t_data *data)
{
	Command	*curr_cmd;

	curr_cmd = data->cmd;
	while (curr_cmd != NULL)
	{
		curr_cmd->redir_erros = 0;
		curr_cmd->fdin = 0;
		curr_cmd->fdout = 1;
		curr_cmd->dup = 0;
		curr_cmd = curr_cmd->next;
	}
}

int	count_env_nodes(t_env_node *env_list)
{
	int	count;

	count = 0;
	while (env_list)
	{
		count++;
		env_list = env_list->next;
	}
	return (count);
}

char	*create_env_entry(t_env_node *node)
{
	char	*temp;
	char	*env_entry;

	env_entry = NULL;
	temp = ft_strjoin(node->name, "=");
	if (temp)
	{
		if (node->value)
			env_entry = ft_strjoin(temp, node->value);
		else
			env_entry = ft_strdup(temp);
		free(temp);
	}
	return (env_entry);
}

char	**list_to_char(t_env_node *env_list)
{
	t_env_node	*cur;
	char		**env_array;
	int			count;
	int			i;

	cur = env_list;
	count = count_env_nodes(env_list);
	i = 0;
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	while (cur)
	{
		env_array[i] = create_env_entry(cur);
		if (!env_array[i])
		{
			while (i > 0)
				free(env_array[--i]);
			return (free(env_array), NULL);
		}
		i++;
		cur = cur->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
