
#include "minishell.h"

bool	ft_str_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	exit_check(t_token *token)
{
	if (!token)
		return (false);
	if (!(!ft_strncmp(token->str, "exit", 4) && ft_strlen(token->str) == 4))
		return (false);
	if (token_list_size(token) > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		g_status = 1;
		free_token(token);
		token = NULL;
		return (true);
	}
	else
	{
		ft_putendl_fd("exit", 2);
		if (!token->next)
			exit(WEXITSTATUS(g_status));
		if (!ft_str_isdigit(token->next->str))
		{
			ft_putendl_fd("minishell: exit: h: numeric argument required", 2);
			g_status = 258 * 2;
		}
		exit(WEXITSTATUS(g_status));
	}
}
