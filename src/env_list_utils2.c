/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:42:11 by jtakahas          #+#    #+#             */
/*   Updated: 2024/07/20 13:57:12 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_key_value(t_key_value *key_value)
{
	t_env	*env;

	if (!key_value)
		return (NULL);
	env = malloc(sizeof(t_env));
	if (!env)
		ft_error("malloc", "env", strerror(errno), EXIT_FAILURE);
	env->key = key_value->key;
	env->value = key_value->value;
	env->is_export = false;
	env->next = NULL;
	return (env);
}

void	export_env(char *key, char *value, t_env **env)
{
	t_env	*tmp;
	char	*tmp_value;
	char	*key_value;

	tmp = *env;
	if (!value)
	{
		value = get_env_value(key, *env);
		if (!value)
			return ;
	}
	while (tmp)
	{
		if (ft_strlen(tmp->key) == ft_strlen(key)
			&& !ft_strncmp(tmp->key, key, ft_strlen(key)))
		{
			tmp_value = tmp->value;
			tmp->value = ft_strdup(value);
			free(tmp_value);
			return ;
		}
		tmp = tmp->next;
	}
	key_value = ft_strjoin(key, ft_strjoin("=", value));
	env_add_back(new_valiable(key_value), env);
}

char	*get_env_value(char *key, t_env *env)
{
	t_env	*tmp;
	int		key_len;

	if (!key)
		return (NULL);
	tmp = env;
	key_len = ft_strlen(key);
	if (key_len == 1 && key[0] == '?')
		return (ft_itoa(error_status(PRINT_ERROR)));
	while (tmp)
	{
		if ((int)ft_strlen(tmp->key) == key_len
			&& !ft_strncmp(tmp->key, key, key_len))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}
