/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:37:52 by yozainan          #+#    #+#             */
/*   Updated: 2024/08/08 12:18:03 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remov_env(t_env_node **env, t_env_node *elem)
{
	t_env_node	*current;
	t_env_node	*prev;

	current = *env;
	prev = NULL;
	while (current)
	{
		if (current == elem)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

t_env_node	*find_env(t_env_node *env, const char *name)
{
	while (env)
	{
		if (strcmp(env->name, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

// void unset_env(char *arg, t_env_node **env)
// {
//     t_env_node *curr;

//     if (!*env)
//         return ;

//     if (arg && !ft_isalpha(arg[0]) && arg[0] != '_')
//     {
//         printf("minishell: unset: `%s`: not a valid identifier\n", arg);
//         g_data.exit_status = EXIT_FAILURE;
//     }
//     else
//     {
//         curr = find_env(*env, arg);
//         if (curr)
//             remov_env(env, curr);
//     }
// }

void	unset_env(char *arg, t_env_node **env)
{
	t_env_node	*curr;

	if (!*env)
		return ;
	curr = find_env(*env, arg);
	if (curr)
		remov_env(env, curr);
}

void	build_unset(t_data *data)
{
	int	i;

	i = 1;
	while (data->cmd->av[i])
	{
		unset_env(data->cmd->av[i], &(data->env_list));
		i++;
	}
	data->exit_status = 0;
}
