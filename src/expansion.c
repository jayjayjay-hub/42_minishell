/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:27:12 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/20 12:52:20 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	variable_expansion(char **str, char **tmp, t_index *index, t_env *env)
{
	char	*key;
	char	*value;
	char	*tmp2;

	key = get_variable_key((*str) + (*index).i + 1);
	value = get_env_value(key, env);
	if (value)
	{
		tmp2 = ft_strjoin(*tmp, value);
		free(*tmp);
		*tmp = tmp2;
		(*index).i += ft_strlen(key) + 1;
		(*index).j += ft_strlen(value);
		free(key);
		free(value);
	}
	else
	{
		(*tmp)[(*index).j] = (*str)[(*index).i];
		((*index).j)++;
		((*index).i)++;
	}
}

void	pass_single_quote(char **tmp, char **str, int *i, int *j)
{
	(*tmp)[*j] = (*str)[*i];
	(*i)++;
	(*j)++;
	while ((*str)[*i] && !is_single_quote((*str)[*i]))
	{
		(*tmp)[*j] = (*str)[*i];
		(*i)++;
		(*j)++;
	}
	(*tmp)[*j] = (*str)[*i];
	(*i)++;
	(*j)++;
}

void	expansion_double_quote(char **str,
	char **tmp, t_index *index, t_env *env)
{
	(*tmp)[(*index).j] = (*str)[(*index).i];
	((*index).i)++;
	((*index).j)++;
	while ((*str)[(*index).i] && !is_double_quote((*str)[(*index).i]))
	{
		if ((*str)[(*index).i] == '$' && (*str)[(*index).i + 1])
			variable_expansion(str, tmp, index, env);
		else
		{
			(*tmp)[(*index).j] = (*str)[(*index).i];
			((*index).i)++;
			((*index).j)++;
		}
	}
	(*tmp)[(*index).j] = (*str)[(*index).i];
	((*index).i)++;
	((*index).j)++;
}

void	expansion_env(char **str, t_env *env)
{
	t_index	index;
	char	*tmp;

	index.i = 0;
	index.j = 0;
	tmp = ft_calloc(1, sizeof(char) * (ft_strlen(*str) + 1));
	while ((*str)[index.i])
	{
		if (is_single_quote((*str)[index.i]))
			pass_single_quote(&tmp, str, &index.i, &index.j);
		else if (is_double_quote((*str)[index.i]))
			expansion_double_quote(str, &tmp, &index, env);
		else if ((*str)[index.i] == '$' && (*str)[index.i + 1])
			variable_expansion(str, &tmp, &index, env);
		else
			tmp[index.j++] = (*str)[index.i++];
	}
	tmp[index.j] = '\0';
	free(*str);
	*str = tmp;
}

void	expansion(t_token *token, t_env *env)
{
	while (token)
	{
		if (token->type == WORD)
		{
			if (token->prev && token->prev->type != REDIRECT_HERE_DOC)
				expansion_env(&token->str, env);
			remove_quote(token->str);
		}
		token = token->next;
	}
}
