
#include "minishell.h"

bool builtin_control(t_ats *ats)
{
	if (ats_list_size(ats) != 1 || ats->token->type != WORD)
		return (false);
	if (ft_strlen(ats->token->str) == 4 && !ft_strncmp(ats->token->str, "exit", 4))
		builtin_exit(ats->token);
	else if (ft_strlen(ats->token->str) == 2 && !ft_strncmp(ats->token->str, "cd", 3))
		builtin_cd(ats->token);
	else if (ft_strlen(ats->token->str) == 4 && !ft_strncmp(ats->token->str, "echo", 5))
		builtin_echo(ats->token);
	else if (ft_strlen(ats->token->str) == 3 && !ft_strncmp(ats->token->str, "pwd", 4))
		builtin_pwd(ats->token);
	// export
	else if (ft_strlen(ats->token->str) == 6 && !ft_strncmp(ats->token->str, "export", 7))
		builtin_export(ats->token);
	// env
	else if (ft_strlen(ats->token->str) == 3 && !ft_strncmp(ats->token->str, "env", 4))
		builtin_env(ats->token);
	else
		return (false);
	return (true);
}
