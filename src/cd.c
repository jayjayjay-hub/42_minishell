#include "minishell.h"

// まだ全然ダメ（そもそもやり方ちょっと違う）
void	cd(char **cmd)
{
	char	*path;
	// パスがNULLまたは空文字列の場合はホームディレクトリに変更
	if (!cmd[1] || strcmp(cmd[1], "") == 0)
	{
		path = strdup(getenv("HOME"));
		if (path == NULL)
			ft_error("cd", "HOME not set", NULL, 1);
		printf("path: %s\n", path);
	}
	// カレントディレクトリを変更
	if (chdir(path) == -1)
		ft_error("cd", cmd[1], strerror(errno), 1);
	exit(0);
}
