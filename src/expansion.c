#include "minishell.h"

void	remove_single_quote(char *str)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_double_quote(str[i]))
		{
			str[j++] = str[i++];
			while (str[i] && !is_double_quote(str[i]))
				str[j++] = str[i++];
		}
		else if (str[i] == '\'')
			i++;
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
}

char	*get_variable_key(char *str)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	j = 0;
	key = NULL;
	i++;
	while (str[i] && is_alnum_under(str[i]))
		i++;
	if (str[i] && str[i] == ' ' || str[i] == '\0' || str[i] == '\"')
		key = ft_substr(str, 1, i - 1);
	return (NULL);
}

void	remove_double_quote(char *str)
{
	int		i;
	int		j;
	int		k;
	char	*key;
	char	*value;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_double_quote(str[i]))
		{
			i++;
			while (str[i] && !is_double_quote(str[i]))
			{
				if (str[i] == '$')
				{
					key = get_variable_key(&str[i]);
					printf("key = %s\n", key);
					if (key)
					{
						value = get_variable_value(key);
						printf("value = %s\n", value);
						free(key);
						if (value)
						{
							// realloc
							str = realloc(str, ft_strlen(str) + ft_strlen(value) + 1);
							k = 0;
							while (value[k])
								str[j++] = value[k++];
							free(value);
							i += ft_strlen(key + 1);
						}
					}
				}
				else
					str[j++] = str[i++];
			}
			i++;
		}
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
}

void	expantion(t_token *token)
{
	if (!token)
		return ;
	while (token)
	{
		if (token->type == WORD)
		{
			remove_single_quote(token->str);
			remove_double_quote(token->str);
		}
		token = token->next;
	}
}
