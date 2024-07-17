#include "minishell.h"

// builtin_pwd.c

bool	builtin_pwd(t_token *token)
{
	char	*path;
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
	{
		perror("pwd");
		error_status(256 * 1);
		return (false);
	}
	ft_putendl_fd(buf, 1);
	error_status(0);
	free(buf);
	return (true);
}
