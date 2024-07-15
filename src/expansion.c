#include "minishell.h"

void	remove_quote(char *str)
{
	int i;
	int j;
	char quote;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				str[j++] = str[i++];
			i++;
		}
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
}

void	variable_env(char **str, char **tmp, int *i, int *j)
{
	char *key;
	char *value;
	char quote;
	char *tmp2;

	if ((*str)[*i + 1])
	{
		key = get_variable_key((*str) + *i + 1);
		value = get_env_value(key);
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
	else
	{
		(*tmp)[*j] = (*str)[*i];
		(*j)++;
		(*i)++;
	}
}

void	expansion_env(char **str)
{
	int i;
	int j;
	char quote;
	char *tmp;

	i = 0;
	j = 0;
	tmp = calloc(1, sizeof(char) * (ft_strlen(*str) + 1));
	while ((*str)[i])
	{
		if (is_single_quote((*str)[i]))
		{
			quote = (*str)[i];
			tmp[j++] = (*str)[i++];
			while ((*str)[i] && (*str)[i] != quote)
				tmp[j++] = (*str)[i++];
			tmp[j++] = (*str)[i++];
		}
		else if (is_double_quote((*str)[i]))
		{
			quote = (*str)[i];
			tmp[j++] = (*str)[i++];
			while ((*str)[i] && (*str)[i] != quote)
			{
				if ((*str)[i] == '$')
					variable_env(str, &tmp, &i, &j);
				else
					tmp[j++] = (*str)[i++];
			}
			tmp[j++] = (*str)[i++];
		}
		else if ((*str)[i] == '$')
			variable_env(str, &tmp, &i, &j);
		else
			tmp[j++] = (*str)[i++];
	}
	tmp[j] = '\0';
	free(*str);
	*str = tmp;
}

void	expansion(t_token * token)
{
	while (token)
	{
		if (token->type == WORD)
		{
			expansion_env(&token->str);
			remove_quote(token->str);
		}
		token = token->next;
	}
}
