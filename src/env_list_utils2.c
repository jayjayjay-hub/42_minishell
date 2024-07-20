/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:42:11 by jtakahas          #+#    #+#             */
/*   Updated: 2024/07/20 16:05:43 by jtakahas         ###   ########.fr       */
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
