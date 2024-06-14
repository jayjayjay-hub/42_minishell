#include "minishell.h"

// エラーを出力してプログラムを終了する。
void	ft_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

// コマンドが見つからなかった場合のエラーを出力してプログラムを終了する。
void	cmd_not_found(char *cmd)
{
	write(2, "minishell: ", 11);
	if (cmd)
		write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	exit(127);
}

// 二次元配列を解放する。
void	dp_free(char **arg)
{
	int	i;

	i = -1;
	while (arg[++i])
		free(arg[i]);
	free(arg);
}

// コマンドが存在するパスを検索する。パスが見つかった場合はそのパスを返す。
char	*search_path(char *cmd, char **envp)
{
	char	**paths;
	char	**tmp_free;
	char	*ret;

	while (ft_strncmp(*envp, "PATH", 4))
		envp++;
	paths = ft_split(*envp + 5, ':');
	tmp_free = paths;
	while (*paths)
	{
		*paths = ft_strjoin(*paths, "/");
		*paths = ft_strjoin(*paths, cmd);
		if (access(*paths, F_OK) == 0)
		{
			ret = ft_strdup(*paths);
			dp_free(tmp_free);
			return (ret);
		}
		paths++;
	}
	cmd_not_found(cmd);
	return (NULL);
}

// コマンドを実行する。コマンドが存在しない場合はエラーを出力する。
void	do_execve(char *line, char **envp)
{
	char	**cmd;
	char	*path;

	// tolenizerはここでしている。改良するならここを変える。ex) cmd = tokenizer(line);
	cmd = ft_split(line, ' ');
	if (!cmd[0])
		ft_error();
	// /bin/ls や ./a.outを実行するため。
	if (!ft_strncmp(cmd[0], "/", 1) || !ft_strncmp(cmd[0], "./", 2))
	{
		if (access(cmd[0], F_OK) == -1)
			ft_error();
		path = cmd[0];
	}
	else
		path = search_path(cmd[0], envp);
	execve(path, cmd, envp);
	ft_error();
}

// 子プロセスを生成して子プロセス内でコマンドを実行する。親プロセスでは子プロセスの終了を待つ。
int	run_cmd(char *line, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		ft_error();
	if (pid == 0)
		do_execve(line, envp);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		status;

	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL || (!ft_strncmp(line, "exit", 4)))
			break ;
		if (*line)
		{
			add_history(line);
			status = run_cmd(line, envp);
			free(line);
		}
	}
	exit(status);
}
