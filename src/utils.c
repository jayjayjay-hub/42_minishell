#include "minishell.h"

int	is_metachar(char c)
{
	return (c && ft_strchr("|&;,()<> ", c));
}

int	is_quote(char c)
{
	return (c && ft_strchr("'\"", c));
}

int	is_single_quote(char c)
{
	return (c && c == '\'');
}

int	is_double_quote(char c)
{
	return (c && c == '\"');
}

int	strlen_double_ptr(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
