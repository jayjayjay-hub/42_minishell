#include "minishell.h"

void	del_quote(char **str)
{
	char	*new_str;
	char	quote_char;

	new_str = calloc(1, ft_strlen(*str) + 1);
	while (**str)
	{
		if (is_quote(**str))
		{
			quote_char = **str;
			while (**str && **str != quote_char)
				*new_str++ = *(*str)++;
			if (**str != quote_char)
				ft_error(NULL, NULL, "quote not closed", 1);
			*new_str++ = *(*str)++;
		}
		else
			*new_str++ = *(*str)++;
	}
	*str = new_str;
}

// token のクオート、ダブルクオートを削除する関数
void	remove_quote(t_token *token)
{
	char	*new_str;
	char	quote_char;
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		new_str = calloc(1, ft_strlen(tmp->str) + 1);
		while (*tmp->str)
		{
			if (is_quote(*tmp->str))
			{
				quote_char = *tmp->str;
				while (*tmp->str && *tmp->str != quote_char)
					*new_str++ = *tmp->str++;
				if (*tmp->str != quote_char)
					ft_error(NULL, NULL, "quote not closed", 1);
				*new_str++ = *tmp->str++;
			}
			else
				*new_str++ = *tmp->str++;
		}
		*new_str = '\0';
		tmp->str = new_str - ft_strlen(tmp->str);
		tmp = tmp->next;
	}
}
