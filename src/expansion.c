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

// char	*expansion_variable(char *str)
// {
// 	int i;
// 	int j;
// 	char *key;
// 	char *value;
// 	char quote;
// 	char *tmp;
// 	char *tmp2;

// 	i = 0;
// 	j = 0;
// 	tmp = calloc(1, sizeof(char) * (ft_strlen(str) + 1));
// 	while (str[i])
// 	{
// 		if (is_quote(str[i])) // qoteはそのままコピー
// 		{
// 			quote = str[i];
// 			tmp[j++] = str[i++];
// 			while (str[i] && str[i] != quote)
// 				tmp[j++] = str[i++];
// 			tmp[j++] = str[i++];
// 		}
// 		else if (str[i] == '$')
// 		{
// 			if (str[i + 1])
// 			{
// 				key = get_variable_key(str + i + 1);
// 				value = get_variable_value(key);
// 				if (value)
// 				{
// 					tmp = ft_strjoin(tmp, value);
// 					i += ft_strlen(key) + 1;
// 					j += ft_strlen(value);
// 					free(key);
// 					free(value);
// 				}
// 				else
// 					tmp[j++] = str[i++];
// 			}
// 			else
// 				tmp[j++] = str[i++];
// 		}
// 		else
// 			tmp[j++] = str[i++];
// 	}
// 	tmp[j] = '\0';
// 	return (tmp);
// }


void	expansion_variable(char **str)
{
	int i;
	int j;
	char *key;
	char *value;
	char quote;
	char *tmp;
	char *tmp2;

	i = 0;
	j = 0;
	tmp = calloc(1, sizeof(char) * (ft_strlen(*str) + 1));
	while ((*str)[i])
	{
		if (is_quote((*str)[i])) // quoteはそのままコピー
		{
			quote = (*str)[i];
			tmp[j++] = (*str)[i++];
			while ((*str)[i] && (*str)[i] != quote)
				tmp[j++] = (*str)[i++];
			tmp[j++] = (*str)[i++];
		}
		else if ((*str)[i] == '$')
		{
			if ((*str)[i + 1])
			{
				key = get_variable_key((*str) + i + 1);
				value = get_variable_value(key);
				if (value)
				{
					tmp2 = ft_strjoin(tmp, value);
					free(tmp);
					tmp = tmp2;
					i += ft_strlen(key) + 1;
					j += ft_strlen(value);
					free(key);
					free(value);
				}
				else
					tmp[j++] = (*str)[i++];
			}
			else
				tmp[j++] = (*str)[i++];
		}
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
			expansion_variable(&token->str);
			remove_quote(token->str);
		}
		token = token->next;
	}
}
