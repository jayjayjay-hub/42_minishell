// cd.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
void	ft_error(char *cmd, char *arg, char *msg, int status)
{
	if (cmd)
	{
		write(2, "minishell: ", 11);
		write(2, cmd, strlen(cmd));
		write(2, ": ", 2);
	}
	if (arg)
	{
		write(2, arg, strlen(arg));
		write(2, ": ", 2);
	}
	if (msg)
	{
		write(2, msg, strlen(msg));
		write(2, "\n", 1);
	}
	exit(status);
}

// cdコマンドを再実装する関数
void	cd(char **cmd)
{
	char	*path;
	// パスがNULLまたは空文字列の場合はホームディレクトリに変更
	if (!cmd[1] || strcmp(cmd[1], "") == 0)
	{
		path = strdup(getenv("HOME"));
		if (path == NULL)
			ft_error("cd", "HOME not set", NULL, 1);
	}
	// カレントディレクトリを変更
	if (chdir(path) == -1)
		ft_error("cd", cmd[1], strerror(errno), 1);
}

// テスト用のmain関数
int main(int argc, char **argv, char **envp)
{
	char	*cmd[2] = {"cd", ""};
	cd(cmd);
	return (0);
}
