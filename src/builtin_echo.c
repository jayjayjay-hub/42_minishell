#include "minishell.h"

// builtin_echo.c

bool	check_option(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (false);
	else
	{
		while (str[i] && str[i] == 'n')
			i++;
		if (str[i])
			return (false);
	}
	return (true);
}

bool	builtin_echo(t_token *token)
{
	bool	newline;

	newline = true;
	if (token->next && check_option(token->next->str))
	{
		newline = false;
		token = token->next;
	}
	token = token->next;
	while (token && check_option(token->str))
		token = token->next;
	while (token && token->type == WORD)
	{
		write(1, token->str, ft_strlen(token->str));
		token = token->next;
		if (token)
			write(1, " ", 1);
	}
	if (newline)
		write(1, "\n", 1);
	error_status(0);
	return (true);
}
