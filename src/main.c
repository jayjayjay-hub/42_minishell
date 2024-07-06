#include "minishell.h"

// eofが来た場合の処理
void	handle_eof(int status, char *line)
{
	write(2, "exit\n", 5);
	if (line)
		free(line);
	exit(WEXITSTATUS(status));
}

void	struct_init(t_ats **ats, t_token **token, t_pipe_fd **fd_pipe, t_pid_info *pid_info)
{
	*ats = NULL;
	*token = NULL;
	*fd_pipe = NULL;
	pid_info->pipe_i = 0;
	pid_info = NULL;
}

// 子プロセスを生成して子プロセス内でコマンドを実行する。親プロセスでは子プロセスの終了を待つ。
// こっちでcmd = tokenizer(line)をして兄弟プロセスを作る予定。|や;で区切ってそれまでを二重配列にして入れる。
int	run_cmd(char *line, char **envp)
{
	t_ats	*ats;
	t_ats	*tmp_ats;
	t_token	*token;
	t_pipe_fd	*fd_pipe;
	t_pid_info pid_info;
	int i = 0;
	int status = 0;

	struct_init(&ats, &token, &fd_pipe, &pid_info);
	token = tokenize(line, &status);
	expantion(token);
	ats = parser(token);
	tmp_ats = ats;
	if (ats)
		fd_pipe = create_pipe(ats);
	while (ats)
	{
		if (token_list_size(ats->token) == 1)
		{
			add_variable(ats->token->str);
			// variable_list_print();
			ats = ats->next;
			continue;
		}
		pid_info.pid[pid_info.pipe_i] = child(ats->token, envp, fd_pipe, pid_info.pipe_i);
		ats = ats->next;
		pid_info.pipe_i++;
	}
	close_pipe(fd_pipe);
	while (pid_info.pipe_i--)
	{
		// printf("wpid = %d\n", pid_info.pid[i]);
		waitpid(pid_info.pid[i++], &status, 0);
	}
	free_ats(tmp_ats);
	return (status);
}

t_variable *variable = NULL;
int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		status;
	t_pid_info	pid_info;
	int		i;

	status = 0;
	errno = 0; // エラー番号をリセット
	register_signal();
	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL || (!ft_strncmp(line, "exit", 4) && ft_strlen(line) == 4))
			handle_eof(status, line);
		if (*line)
		{
			i = 0;
			add_history(line);
			status = run_cmd(line, envp);
			// while (pid_info.pipe_i--)
			// {
			// 	printf("wpid = %d\n", pid_info.pid[i]);
			// 	waitpid(pid_info.pid[i++], &status, 0);
			// }
			// printf("status = %d\n", WEXITSTATUS(status));
			free(line);
		}
	}
	return (WEXITSTATUS(status));
}

// int main(int argc, char **argv, char **envp)
// {
// 	int status = 0;
// 	t_pid_info pid_info;
// 	int i = 0;
// 	char *line = "echo a > out| echo b >> out| echo c >> out| echo d > out| cat out";

// 	pid_info = run_cmd(line, envp);
// 	while (pid_info.pipe_i--)
// 	{
// 		waitpid(pid_info.pid[i], &status, 0);
// 		i++;
// 	}
// 	return(WEXITSTATUS(status));
// }

// valgrind --leak-check=full -s ./minishell
