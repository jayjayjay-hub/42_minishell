
#include "minishell.h"

bool	exit_check(t_token *token)
{
	if (!token)
		return (false);
	if (!(!ft_strncmp(token->str, "exit", 4) && ft_strlen(token->str) == 4))
	{
		// printf("exit_check: %s\n", token->str);
		return (false);
	}
	if (token_list_size(token) > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		g_status = 1;
		free_token(token);
		token = NULL;
		return (false);
	}
	else
	{
		ft_putendl_fd("exit", 2);
		exit(WEXITSTATUS(g_status));
	}
}