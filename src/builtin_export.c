/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:26:07 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/17 16:15:04 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	error_export(t_env *env)
{
	print_export(env);
	return (true);
}

bool	builtin_export(t_token *token, t_env **env)
{
	char	*key;
	char	*value;
	int		key_len;

	if (!token->next)
		return (error_export(*env));
	token = token->next;
	while (token)
	{
		key_len = 0;
		while (token->str[key_len] && token->str[key_len] != '=')
			key_len++;
		if (token->str[key_len] == '=')
		{
			key = ft_substr(token->str, 0, key_len);
			value = ft_strdup(token->str + key_len + 1);
			export_env(key, value, env);
			free(key);
			free(value);
		}
		else
			export_env(token->str, NULL, env);
		token = token->next;
	}
	return (error_status(0), true);
}
