#include "minishell.h"

bool	is_alnum_under(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (true);
	return (false);
}

bool	is_al_under(char c)
{
	if (c == '_' || ft_isalpha(c))
		return (true);
	return (false);
}

bool	is_valid_variable(char *str)
{
	int	index;

	index = 0;
	if (!str)
		return (false);
	if (!is_al_under(str[index]))
		return (false);
	index++;
	while (str[index] && is_alnum_under(str[index]))
		index++;
	if (!str[index] || str[index] != '=')
		return (false);
	index++;
	if (!str[index])
		return (false);
	return (true);
}

t_key_value *get_key_value(char *str)
{
	t_key_value	*key_value;
	char		*tmp;
	int			key_len;

	key_value = (t_key_value *)malloc(sizeof(t_key_value));
	if (!key_value)
		return (NULL);
	tmp = strchr(str, '=');
	if (!tmp)
	{
		free(key_value);
		return (NULL);
	}
	key_len = tmp - str;
	key_value->key = ft_substr(str, 0, key_len);
	key_value->value = ft_strdup(tmp + 1);
	return (key_value);
}

bool	add_variable(t_token *token)
{
	t_env	*new;
	t_key_value	*key_value;

	while (token)
	{
		if (!is_valid_variable(token->str))
			return (false);
		key_value = get_key_value(token->str);
		if (edit_env_value(key_value->key, key_value->value))
		{
			free(key_value->key);
			free(key_value->value);
			token = token->next;
			continue ;
		}
		new = new_key_value(key_value);
		if (!new)
			return (false);
		add_back_env(new);
		token = token->next;
	}
	return (true);
}
