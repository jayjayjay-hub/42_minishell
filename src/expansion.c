/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:27:12 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/22 14:02:43by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*variable_expansion(char *str, t_env *env, int *str_index)
{
	char *key;
	char *value;

	str++;
	key = get_key(str);
	if (!key)
		return (NULL);
	value = get_env_value(key, env);
	*str_index += ft_strlen(key) + 1;
	free(key);
	return (value);
}

// void	variable_expansion(char **str, char **tmp, t_index *index, t_env *env)
// {
// 	char	*key;
// 	char	*value;
// 	char	*tmp2;

// 	key = get_variable_key((*str) + (*index).i + 1);
// 	value = get_env_value(key, env);
// 	if (value)
// 	{
// 		tmp2 = ft_strjoin(*tmp, value);
// 		free(*tmp);
// 		*tmp = tmp2;
// 		(*index).i += ft_strlen(key) + 1;
// 		(*index).j += ft_strlen(value);
// 		free(key);
// 		free(value);
// 	}
// 	else
// 	{
// 		(*tmp)[(*index).j] = (*str)[(*index).i];
// 		((*index).j)++;
// 		((*index).i)++;
// 	}
// }

char	*pass_single_quote(char *str, int *str_index)
{
	int index;
	index = 0;
	index++;
	while (str[index] && !is_single_quote(str[index]))
		index++;
	index++;
	*str_index += index;
	return (ft_substr(str, 0, index));
}

// void	pass_single_quote(char **tmp, char **str, int *i, int *j)
// {
// 	(*tmp)[*j] = (*str)[*i];
// 	(*i)++;
// 	(*j)++;
// 	while ((*str)[*i] && !is_single_quote((*str)[*i]))
// 	{
// 		(*tmp)[*j] = (*str)[*i];
// 		(*i)++;
// 		(*j)++;
// 	}
// 	(*tmp)[*j] = (*str)[*i];
// 	(*i)++;
// 	(*j)++;
// }

void expansion_env(char **str, t_env *env)
{
	int index;
	char *tmp;
	char *free_tmp;
	char *value;

	index = 0;
	free_tmp = ft_calloc(1, sizeof(char) * (ft_strlen(*str) + 1));
	while ((*str)[index])
	{
		if (is_single_quote((*str)[index]))
		{
			tmp = ft_strjoin(free_tmp, pass_single_quote(*str + index, &index));
			free(free_tmp);
			free_tmp = tmp;
		}
		else if ((*str)[index] == '$' && (*str)[index + 1])
		{
			value = variable_expansion(*str + index, env, &index);
			if (value)
			{
				tmp = ft_strjoin(free_tmp, value);
				free(free_tmp);
				free(value);
				free_tmp = tmp;
			}
		}
		else if ((*str)[index])
		{
			tmp = ft_strjoin(free_tmp, ft_substr(*str + index, 0, 1));
			free(free_tmp);
			free_tmp = tmp;
			index++;
		}
	}
	free(*str);
	*str = free_tmp;
}

		// t_index	index;
		// char	*tmp;

		// index.i = 0;
		// index.j = 0;
		// tmp = ft_calloc(1, sizeof(char) * (ft_strlen(*str) + 1));
		// while ((*str)[index.i])
		// {
		// 	if (is_single_quote((*str)[index.i]))
		// 		pass_single_quote(&tmp, str, &index.i, &index.j);
		// 	else if ((*str)[index.i] == '$' && (*str)[index.i + 1])
		// 		variable_expansion(str, &tmp, &index, env);
		// 	else
		// 		tmp[index.j++] = (*str)[index.i++];
		// }
		// tmp[index.j] = '\0';
		// free(*str);
		// *str = tmp;

	void expansion(t_token * token, t_env * env)
	{
		while (token)
		{
			if (token->type == WORD)
			{
				if (token->prev && token->prev->type != REDIRECT_HERE_DOC)
					expansion_env(&token->str, env);
				else if (token_list_size(token) == 1)
					expansion_env(&token->str, env);
				remove_quote(token->str);
			}
			token = token->next;
		}
	}
