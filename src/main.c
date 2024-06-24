#include "minishell.h"

// eofが来た場合の処理
void	handle_eof(int status, char *line)
{
	write(2, "exit\n", 5);
	if (line)
		free(line);
	exit(WEXITSTATUS(status));
}

// 子プロセスを生成して子プロセス内でコマンドを実行する。親プロセスでは子プロセスの終了を待つ。
// こっちでcmd = tokenizer(line)をして兄弟プロセスを作る予定。|や;で区切ってそれまでを二重配列にして入れる。
int	run_cmd(char *line, char **envp)
{
	t_ats	*ats;
	t_token	*token;
	t_ats	*tmp_ats;
	int		ret = 0;
	int		*fd_pipe;

	token = tokenize(line);
	ats = parser(token);
	tmp_ats = ats;
	// 親プロセスで兄弟プロセスを作る予定while(pipe数){pipe();fork()}
	if (ats)
		fd_pipe = create_pipe(ats);
	while (ats)
	{
		child(ats->token, envp, fd_pipe, ret);
		ats = ats->next;
		ret++;
	}
	free_ats(tmp_ats);
	return (ret);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		status;
	int		i;

	status = 0;
	errno = 0; // エラー番号をリセット
	register_signal();
	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL || (!ft_strncmp(line, "exit", 4)))
			handle_eof(status, line);
		if (*line)
		{
			add_history(line);
			i = run_cmd(line, envp);
			// while (i--)
				waitpid(-1, &status, 0);
			free(line);
		}
	}
	exit(WEXITSTATUS(status));
}

// int main(int argc, char **argv, char **envp)
// {
// 	int status = 0;
// 	t_token *token;
// 	t_ats *ats;
// 	int i;

// 	// char *line = "nosuchcommand";
// 	char *line = "ls | ls | ajklsf";
// 	i = run_cmd(line, envp);
// 	while (i--)
// 	{
// 		printf("i= %d\n", i);
// 		waitpid(-1, &status, 0);
// 		printf("status= %d\n", status);
// 	}
// 	exit(WEXITSTATUS(status));
// }

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q minishell");
// }
