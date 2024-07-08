#include "minishell.h"

int is_metachar(char c)
{
	return (c && strchr("|&;,()<> ", c)); // https://runebook.dev/ja/docs/bash/definitions
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
