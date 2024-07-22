/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:26:55 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/22 14:11:48 by jtakahas         ###   ########.fr       */
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

bool	edit_env_value(char *key, char *value, t_env **env)
{
	t_env	*tmp;
	char	*tmp_value;
	int		key_len;

	tmp = *env;
	key_len = ft_strlen(key);
	while (tmp)
	{
		if ((int)ft_strlen(tmp->key) == key_len
			&& !ft_strncmp(tmp->key, key, key_len))
		{
			tmp_value = tmp->value;
			tmp->value = ft_strdup(value);
			free(tmp_value);
			return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}

char	*get_env_value(char *key, t_env *env)
{
	t_env	*tmp;
	int		key_len;

	tmp = env;
	if (!key)
		return (NULL);
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

char	*get_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	if (ft_strlen(str) == 1 && str[0] == '?')
		return (ft_strdup("?"));
	if (!is_al_under(str[i]))
		return (NULL);
	i++;
	while (str[i] && is_alnum_under(str[i]))
		i++;
	key = ft_substr(str, 0, i);
	return (key);
}

t_env	*new_env(char *env_line, bool is_export)
{
	t_env	*env;
	char	*key;
	char	*value;

	env = malloc(sizeof(t_env));
	if (!env)
		ft_error("malloc", "env", strerror(errno), EXIT_FAILURE);
	key = get_key_from_str(env_line);
	if (!key)
		return (NULL);
	value = get_value_from_str(env_line);
	env->key = key;
	env->value = value;
	env->is_export = is_export;
	env->next = NULL;
	return (env);
}
