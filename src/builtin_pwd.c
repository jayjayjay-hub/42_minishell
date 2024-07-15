#include "minishell.h"

// builtin_pwd.c

bool	builtin_pwd(t_token *token)
{
	char	*path;
	char	*buf;

	// debug
	// printf("builtin_pwd\n");
	// todo コメントアウトしてるif文いらないと思うんだけど確認よろしく
	// 確かにそうだわいらないわ
	buf = getcwd(NULL, 0);
	if (!buf)
	{
		perror("pwd");
		g_status = 1;
		return (false);
	}
	ft_putendl_fd(buf, 1);
	free(buf);
	return (true);
}
