
#include "minishell.h"

bool	ft_str_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			return (false);
		i++;
	}
	return (true);
}

bool	builtin_exit(t_token *token)
{
	if (token_list_size(token) > 2)
	{
		ft_putendl_fd("exit", 2);
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		g_status = 256;
		return (true);
	}
	else
	{
		ft_putendl_fd("exit", 2);
		if (!token->next)
			exit(g_status);
		else if (!ft_str_isdigit(token->next->str))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(token->next->str, 2);
			ft_putendl_fd(": numeric argument required", 2);
			g_status = 2;
		}
		else
			g_status = (size_t)ft_atoi(token->next->str);
		exit(g_status);
	}
}
