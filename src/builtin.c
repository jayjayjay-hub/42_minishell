
#include "minishell.h"

bool builtin_control(t_token *token)
{
	if (token->type != WORD)
		return (false);
	if (ft_strlen(token->str) == 4 && !ft_strncmp(token->str, "exit", 4))
		builtin_exit(token);
	else if (ft_strlen(token->str) == 2 && !ft_strncmp(token->str, "cd", 3))
		builtin_cd(token);
	else if (ft_strlen(token->str) == 4 && !ft_strncmp(token->str, "echo", 5))
		builtin_echo(token);
	else if (ft_strlen(token->str) == 3 && !ft_strncmp(token->str, "pwd", 4))
		builtin_pwd(token);
	// export
	else if (ft_strlen(token->str) == 6 && !ft_strncmp(token->str, "export", 7))
		builtin_export(token);
	// env
	else if (ft_strlen(token->str) == 3 && !ft_strncmp(token->str, "env", 4))
		builtin_env(token);
	else
		return (false);
	return (true);
}
