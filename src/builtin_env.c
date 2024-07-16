#include "minishell.h"

// builtin_env.c

bool	builtin_env(t_token *token, t_env *env)
{
	print_env(env);
	return (true);
}
