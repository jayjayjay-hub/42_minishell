
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

// debug用。二次元配列を出力する。
void	dp_print(char **arg)
{
	int	i;

	i = -1;
	while (arg[++i])
		ft_putendl_fd(arg[i], 2);
}

static void	sub_dup2(int first, int second)
{
	if (first != 0)
		dup2(first, STDIN_FILENO);
	if (second != 0)
		dup2(second, STDOUT_FILENO);
}

// コマンドが存在するパスを検索する。パスが見つかった場合はそのパスを返す。
char	*search_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*tmp_ret;
	char	*ret;

	i = 0;
	while (*envp && ft_strncmp(*envp, "PATH", 4))
		envp++;
	paths = ft_split(*envp + 5, ':');
	while (paths[i])
	{
		tmp_ret = ft_strjoin(paths[i], "/");
		ret = ft_strjoin(tmp_ret, cmd);
		if (access(ret, F_OK) == 0)
		{
			dp_free(paths);
			free(tmp_ret);
			return (ret);
		}
		free(tmp_ret);
		free(ret);
		i++;
	}
	dp_free(paths);
	return (NULL);
}

// コマンドを実行する。コマンドが存在しない場合はエラーを出力する。
void	do_execve(char **cmd, char **envp)
{
	char	*path;

	// /bin/ls や ./a.outを実行するため。
	path = NULL;
	if (!ft_strncmp(cmd[0], "/", 1) || !ft_strncmp(cmd[0], "./", 2))
	{
		if (access(cmd[0], F_OK) != -1)
			path = cmd[0];
		else
			ft_error("minishell", cmd[0], "No such file or directory", CMD_NOT_FOUND);
	}
	else
		path = search_path(cmd[0], envp);
	if (!path)
		ft_error("minishell", cmd[0], "command not found", CMD_NOT_FOUND);
	if (execve(path, cmd, envp) == -1)
		ft_error(NULL, NULL, "execve failed", EXIT_FAILURE);
}

char	**get_cmd(t_token *token)
{
	int			i;
	char	**cmd;

	i = 0;
	cmd = (char **)ft_calloc(token_list_size(token) + 1, sizeof(char *));
	if (!cmd)
		ft_error("malloc", "cmd", "malloc failed", 1);
	while (token)
	{
		while (token && token->type == WORD)
		{
			cmd[i] = ft_strdup(token->str);
			if (!cmd[i])
				ft_error("malloc", "cmd", "malloc failed", 1);
			token = token->next;
			i++;
		}
		redirect(&token);
	}
	return (cmd);
}

pid_t	child(t_token *token, char **envp, t_pipe_fd *fd_pipe, int pipe_i)
{
	pid_t	pid;
	char	**cmd;

	pid = fork();
	if (pid == -1)
		ft_error("minishell", NULL, "fork failed", 1);
	if (pid == 0)
	{
		if (fd_pipe->pipe_size != 0)
		{
			if (pipe_i == 0)
				sub_dup2(0, fd_pipe->fd[2 * pipe_i + 1]);
			else if (pipe_i == fd_pipe->pipe_size)
				sub_dup2(fd_pipe->fd[2 * pipe_i - 2], 0);
			else
				sub_dup2(fd_pipe->fd[2 * pipe_i - 2], fd_pipe->fd[2 * pipe_i + 1]);
		}
		close_pipe(fd_pipe);
		cmd = get_cmd(token);
		do_execve(cmd, envp);
	}
	return (pid);
}
