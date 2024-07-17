/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:27:12 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/17 15:42:47 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	variable_expansion(char **str, char **tmp, int *i, int *j, t_env *env)
{
	char	*key;
	char	*value;
	char	quote;
	char	*tmp2;

	key = get_variable_key((*str) + *i + 1);
	value = get_env_value(key, env);
	if (value)
	{
		tmp2 = ft_strjoin(*tmp, value);
		free(*tmp);
		*tmp = tmp2;
		*i += ft_strlen(key) + 1;
		*j += ft_strlen(value);
		free(key);
		free(value);
	}
	else
	{
		(*tmp)[*j] = (*str)[*i];
		(*j)++;
		(*i)++;
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
	char **tmp, int *i, int *j, t_env *env)
{
	(*tmp)[*j] = (*str)[*i];
	(*i)++;
	(*j)++;
	while ((*str)[*i] && !is_double_quote((*str)[*i]))
	{
		if ((*str)[*i] == '$' && (*str)[*i + 1])
			variable_expansion(str, tmp, i, j, env);
		else
		{
			(*tmp)[*j] = (*str)[*i];
			(*i)++;
			(*j)++;
		}
	}
	(*tmp)[*j] = (*str)[*i];
	(*i)++;
	(*j)++;
}

void	expansion_env(char **str, t_env *env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_calloc(1, sizeof(char) * (ft_strlen(*str) + 1));
	while ((*str)[i])
	{
		if (is_single_quote((*str)[i]))
			pass_single_quote(&tmp, str, &i, &j);
		else if (is_double_quote((*str)[i]))
			expansion_double_quote(str, &tmp, &i, &j, env);
		else if ((*str)[i] == '$' && (*str)[i + 1])
			variable_expansion(str, &tmp, &i, &j, env);
		else
			tmp[j++] = (*str)[i++];
	}
	tmp[j] = '\0';
	free(*str);
	*str = tmp;
}

void	expansion(t_token *token, t_env *env)
{
	while (token)
	{
		if (token->type == WORD)
		{
			expansion_env(&token->str, env);
			remove_quote(token->str);
		}
		token = token->next;
	}
}
