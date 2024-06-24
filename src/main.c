#include "minishell.h"

// 子プロセスを生成して子プロセス内でコマンドを実行する。親プロセスでは子プロセスの終了を待つ。
// こっちでcmd = tokenizer(line)をして兄弟プロセスを作る予定。|や;で区切ってそれまでを二重配列にして入れる。
void	run_cmd(char *line, char **envp)
{
	t_ats	*ats;
	t_token	*token;
	t_ats	*tmp_ats;

	token = tokenize(line);
	ats = parser(token);
	tmp_ats = ats;
	// 親プロセスで兄弟プロセスを作る予定while(pipe数){pipe();fork()}
	while (ats)
	{
		child(ats->token, envp);
		ats = ats->next;
	}
	free_ats(tmp_ats);
}

// eofが来た場合の処理
void	handle_eof(int status, char *line)
{
	write(2, "exit\n", 5);
	if (line)
		free(line);
	exit(WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		status;

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
			run_cmd(line, envp);
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
// 	// char *line = "nosuchcommand";
// 	char *line = "ls > test";
// 	run_cmd(line, envp);
// 	exit(WEXITSTATUS(status));
// }

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q minishell");
// }
