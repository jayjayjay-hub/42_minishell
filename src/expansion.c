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

void	expantion(t_token *token)
{
	if (!token)
		return ;
	while (token)
	{
		remove_single_quote(token->str);
		token = token->next;
	}
}
