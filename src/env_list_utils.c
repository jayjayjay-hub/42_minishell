/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:39:46 by jtakahas          #+#    #+#             */
/*   Updated: 2024/07/20 15:59:22 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

int	env_list_size(t_env *env)
{
	int		size;
	t_env	*tmp;

	size = 0;
	tmp = env;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
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
