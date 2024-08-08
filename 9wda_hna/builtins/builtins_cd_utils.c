/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:03:14 by yozainan          #+#    #+#             */
/*   Updated: 2024/08/02 21:32:32 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(t_env_node *env, const char *name)
{
	size_t	len;

	len = ft_strlen(name);
	while (env)
	{
		if (!ft_strncmp(env->name, name, len) && (env->name[len] == '='
				|| env->name[len] == '\0'))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	set_pwd(t_env_node *env_list)
{
	t_env_node	*env;
	char		cwd[PATH_MAX];

	env = env_list;
	if (!getcwd(cwd, PATH_MAX))
	{
		perror("getcwd");
		g_data.exit_status = EXIT_FAILURE;
		return ;
	}
	while (env)
	{
		if (!ft_strncmp(env->name, "PWD", 3) && ((env->name[3] == '=')
				|| env->name[3] == '\0'))
		{
			free(env->value);
			env->value = ft_strdup(cwd);
			return ;
		}
		env = env->next;
	}
}

void	set_oldpwd(t_env_node *env_list)
{
	t_env_node	*env;
	char		cwd[PATH_MAX];

	env = env_list;
	if (!getcwd(cwd, PATH_MAX))
	{
		g_data.exit_status = EXIT_FAILURE;
		return ;
	}
	while (env)
	{
		if (!ft_strncmp(env->name, "OLDPWD", 6) && ((env->name[6] == '=')
				|| env->name[6] == '\0'))
		{
			free(env->value);
			env->value = ft_strdup(cwd);
			return ;
		}
		env = env->next;
	}
}

void	update_env_var(t_env_node **env_list, char *name, char *new)
{
	t_env_node	*node;

	node = *env_list;
	while (node)
	{
		if (!ft_strcmp(node->name, name))
		{
			free(node->value);
			node->value = ft_strdup(new);
			return ;
		}
		node = node->next;
	}
}

void	swap_pwd_oldpwd(t_data *data)
{
	char	*oldpwd;
	char	cwd[PATH_MAX];

	oldpwd = ft_getenv(data->env_list, "OLDPWD");
	if (!oldpwd)
	{
		printf("minishell: cd: OLDPWD not set\n");
		data->exit_status = EXIT_FAILURE;
		return ;
	}
	change_directory(data, oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
}
