
#include "minishell.h"

bool	syntax_check(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return (false);
	tmp = token;
	while (tmp)
	{
		if (tmp->type >= PIPE && tmp->type <= REDIRECT_APPEND)
		{
			if (!tmp->next || tmp->next->type != WORD)
			{
				if (!tmp->next)
					ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
				else if (tmp->next->type != WORD)
				{
					ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
					ft_putstr_fd(tmp->str, 2);
					ft_putendl_fd("'", 2);
				}
				g_status = 258 * 2;
				free_token(token);
				return (false);
			}
		}
		tmp = tmp->next;
	}
	return (true);
}
