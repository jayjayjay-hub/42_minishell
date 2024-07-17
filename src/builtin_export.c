/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:26:07 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/17 15:26:12 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	builtin_export(t_token *token, t_env **env)
{
	char	*key;
	char	*value;
	int		key_len;

	if (!token->next)
	{
		print_export(*env);
		return (true);
	}
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
	error_status(0);
	return (true);
}
