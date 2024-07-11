#include "minishell.h"

// builtin_env.c

bool	builtin_env(t_token *token)
{
	print_env();
	return (true);
}
