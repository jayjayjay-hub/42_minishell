#include "minishell.h"

void	ft_error(char *cmd, char *target, char *main_message, int status)
{
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (target)
	{
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(main_message, 2);
	if (status)
		exit(WEXITSTATUS(status));
}
