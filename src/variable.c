#include "minishell.h"

bool	is_alnum_under(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (true);
	return (false);
}

void	add_variable(t_variable **valiable, char *str)
{
	t_variable	*new;
	char		*key;
	char		*value;
	char		*tmp;
	int			key_len;

	tmp = strchr(str, '=');
	if (!tmp)
		return ;
	key_len = 0;
	while (str[key_len] && is_alnum_under(str[key_len]) && str[key_len] != '=')
		key_len++;
	if (str[key_len] != '=')
		return ;
	key = ft_substr(str, 0, key_len);
	value = ft_strdup(tmp + 1);
	new = variable_list_new(key, value);
	variable_list_add_back(valiable, new);
}
