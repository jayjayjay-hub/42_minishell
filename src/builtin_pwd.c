#include "minishell.h"

// builtin_pwd.c

bool	builtin_pwd(t_token *token)
{
	char	*path;
	char	*buf;

	// debug
	// printf("builtin_pwd\n");
	// todo pwd > outに対応できるようにしといたから下のif文調整しといて
	if (token->next)
	{
		write(2, "pwd: too many arguments\n", 25);
		g_status = 256 * 1;
		return (false);
	}
	buf = getcwd(NULL, 0);
	if (!buf)
	{
		perror("pwd");
		g_status = 1;
		return (false);
	}
	write(1, buf, strlen(buf));
	write(1, "\n", 1);
	free(buf);
	return (true);
}
