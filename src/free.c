
#include "minishell.h"

// 二次元配列を解放する。
void	dp_free(char **arg)
{
	int	i;

	i = -1;
	while (arg[++i])
		free(arg[i]);
	free(arg);
}

void	free_command(t_cmd *command)
{
	free(command->fd_pipe->fd);
	free(command->fd_pipe);
	free(command->pid_info.pid);
// 	free_token(command->ats->token); todo
	free_ats(command->ats);
	free(command);
}
