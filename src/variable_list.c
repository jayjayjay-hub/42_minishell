/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:29:02 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/17 15:29:14 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_variable	*variable_list_new(char *key, char *value)
{
	t_variable	*new;

	new = (t_variable *)malloc(sizeof(t_variable));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

char	*get_variable_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	if (ft_strlen(str) == 1 && str[0] == '?')
		return (strdup("?"));
	if (!is_al_under(str[i]))
		return (NULL);
	i++;
	while (str[i] && is_alnum_under(str[i]))
		i++;
	key = ft_substr(str, 0, i);
	return (key);
}
