/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:26:55 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/17 15:40:59 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_add_back(t_env *new, t_env **env)
{
	t_env	*tmp;

	if (!new)
		return ;
	if (!env || !*env)
		*env = new;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

char	*get_key_from_envp(char *env_line)
{
	int		i;
	char	*key;

	i = 0;
	while (env_line[i] && env_line[i] != '=')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		ft_error("malloc", "key", strerror(errno), EXIT_FAILURE);
	ft_strlcpy(key, env_line, i + 1);
	return (key);
}

char	*get_value_from_envp(char *env_line)
{
	int		i;
	char	*value;

	i = 0;
	while (env_line[i] && env_line[i] != '=')
		i++;
	if (!env_line[i])
		return (NULL);
	value = ft_strdup(env_line + i + 1);
	if (!value)
		ft_error("ft_strdup", "value", strerror(errno), EXIT_FAILURE);
	return (value);
}

t_env	*new_valiable(char *env_line)
{
	t_env	*env;
	char	*key;
	char	*value;

	env = malloc(sizeof(t_env));
	if (!env)
		ft_error("malloc", "env", strerror(errno), EXIT_FAILURE);
	key = get_key_from_envp(env_line);
	value = get_value_from_envp(env_line);
	env->key = key;
	env->value = value;
	env->is_export = false;
	env->next = NULL;
	return (env);
}

t_env	*new_export_env(char *env_line)
{
	t_env	*env;
	char	*key;
	char	*value;

	env = malloc(sizeof(t_env));
	if (!env)
		ft_error("malloc", "env", strerror(errno), EXIT_FAILURE);
	key = get_key_from_envp(env_line);
	value = get_value_from_envp(env_line);
	env->key = key;
	env->value = value;
	env->is_export = true;
	env->next = NULL;
	return (env);
}
