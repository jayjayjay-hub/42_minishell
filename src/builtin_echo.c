#include "minishell.h"

// builtin_echo.c

bool	builtin_echo(t_token *token)
{
	bool	newline;

	newline = true;
	// debug
	if (token->next && strlen(token->next->str) == 2 && !strncmp(token->next->str, "-n", 3))
	{
		newline = false;
		token = token->next;
	}
	token = token->next;
	while (token)
	{
		write(1, token->str, strlen(token->str));
		token = token->next;
		if (token)
			write(1, " ", 1);
	}
	if (newline)
		write(1, "\n", 1);
	return (true);
}
