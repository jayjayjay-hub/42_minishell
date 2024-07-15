#include "minishell.h"

// builtin_pwd.c

bool	builtin_pwd(t_token *token)
{
	char	*path;
	char	*buf;

	// debug
	// printf("builtin_pwd\n");
	// 完了 コメントアウトしてるif文いらないと思うんだけど確認よろしく
	// 確かにそうだわいらないわ
	buf = getcwd(NULL, 0);
	if (!buf)
	{
		perror("pwd");
		error_status(256 * 1);
		return (false);
	}
	ft_putendl_fd(buf, 1);
	free(buf);
	return (true);
}
