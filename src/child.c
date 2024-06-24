
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
	if (!ft_strncmp(cmd[0], "/", 1) || !ft_strncmp(cmd[0], "./", 2))
	{
		if (access(cmd[0], F_OK) == -1)
			path = NULL;
		path = cmd[0];
	}
	else
		path = search_path(cmd[0], envp);
	if (!path)
		ft_error("minishell", cmd[0], "command not found", CMD_NOT_FOUND);
	if (execve(path, cmd, envp) == -1)
		ft_error(NULL, NULL, "execve failed", EXIT_FAILURE);
}

void	child(t_token *token, char **envp)
{
	pid_t	pid;
	char	**cmd;
	int		i;

	i = 0;
	pid = fork();
	if (pid == -1)
		ft_error(NULL, NULL, "fork failed", 1);
	if (pid == 0)
	{
		cmd = (char **)malloc(sizeof(char *) * token_list_size(token) + 1);
		if (!cmd)
			ft_error("malloc", "cmd", strerror(errno), 1);
		cmd[token_list_size(token)] = NULL;
		while (token)
		{
			while (token && token->type == WORD)
			{
				// cmd[i] = (char *)malloc(sizeof(char) * ft_strlen(token->str));
				cmd[i] = calloc(1, ft_strlen(token->str) + 1);
				// if (!cmd[i])
				// 	ft_error("malloc", cmd[i], strerror(errno), 1);
				// cmd[i] = token->str;
				strncpy(cmd[i], token->str, ft_strlen(token->str));
				token = token->next;
				i++;
			}
			if (token && ((token->type == REDIRECT_IN) || (token->type == REDIRECT_OUT) || (token->type == REDIRECT_APPEND) || (token->type == REDIRECT_HERE_DOC)))
			{
				redirect(&token);
				token = token->next;
			}
		}
		do_execve(cmd, envp);
		// ここで標準出力入力を戻す必要あり
	}
}
