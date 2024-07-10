#include "minishell.h"

bool builtin_export(t_token *token)
{
	char *key;
	char *value;
	int	key_len;

	if (!token->next)
	{
		print_export_env();
		return (true);
	}
	token = token->next;
	while (token)
	{
		// = までをkeyとして取得
		key_len = 0;
		while (token->str[key_len] && token->str[key_len] != '=')
			key_len++;
		if (token->str[key_len] == '=')
		{
			key = ft_substr(token->str, 0, key_len);
			value = ft_strdup(token->str + key_len + 1);
			export_env(key, value);
			free(key);
			free(value);
		}
		else
			export_env(token->str, NULL);
		token = token->next;
	}
	return (true);
}