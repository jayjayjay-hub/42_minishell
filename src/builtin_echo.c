#include "minishell.h"

// builtin_echo.c

bool	builtin_echo(t_token *token)
{
	bool	newline;

	newline = true;
	if (token->next && ft_strlen(token->next->str) == 2
		&& !ft_strncmp(token->next->str, "-n", 3))
	{
		newline = false;
		token = token->next;
	}
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
