#include "minishell.h"

void	ft_error(char *cmd, char *target, char *main_message, int status)
{
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (target)
	{
		write(2, target, ft_strlen(target));
		write(2, ": ", 2);
	}
	write(2, main_message, ft_strlen(main_message));
	write(2, "\n", 1);
	exit(status);
}
