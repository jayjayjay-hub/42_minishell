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
	int	i;

	i = 0;
	if (!str)
		return (false);
	if (!is_al_under(str[i]))
		return (false);
	i++;
	while (str[i])
	{
		if (!is_alnum_under(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	add_variable(char *str)
{
	t_variable	*new;
	char		*key;
	char		*value;
	char		*tmp;
	int			key_len;

	tmp = strchr(str, '=');
	if (!tmp)
		return (false);
	key_len = 0;
	if (!is_al_under(str[key_len]))
		return (false);
	key_len++;
	while (str[key_len] && is_alnum_under(str[key_len]) && str[key_len] != '=')
		key_len++;
	if (str[key_len] != '=')
		return (false);
	key = ft_substr(str, 0, key_len);
	value = ft_strdup(tmp + 1);
	if (edit_variable(key, value))
	{
		free(key);
		free(value);
		return (true);
	}
	new = variable_list_new(key, value);
	variable_list_add_back(new);
	return (true);
}
