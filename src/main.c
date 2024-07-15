#include "minishell.h"

// eofが来た場合の処理
void	handle_eof(char *line)
{
	write(2, "exit\n", 5);
	if (line)
		free(line);
	exit(WEXITSTATUS(errno));
}

void	struct_init(t_ats *ats, t_token *token, t_pipe_fd *fd_pipe, t_pid_info *pid_info)
{
	ats = NULL;
	token = NULL;
	fd_pipe = NULL;
	pid_info->pid = NULL;
	pid_info->pipe_i = 0;
	pid_info = NULL;
}

void	make_child(t_ats *ats, char **envp, t_pipe_fd *fd_pipe, t_pid_info pid_info)
{
	int i;

	i = 0;
	fd_pipe = create_pipe(ats);
	pid_info.pid = (pid_t *)malloc(sizeof(pid_t) * (fd_pipe->pipe_size + 1));
	while (ats)
	{
		if (token_list_size(ats->token) == 1)
		{
			if (add_variable(ats->token->str))
			{
				// variable_list_print();
				ats = ats->next;
				continue ;
			}
		}
		if (!fd_pipe->pipe_size && builtin_control(ats->token))
		{
			ats = ats->next;
			continue ;
		}
		pid_info.pid[pid_info.pipe_i] = child(ats->token, envp, fd_pipe, pid_info.pipe_i);
		pid_info.pipe_i++;
		ats = ats->next;
	}
	close_pipe(fd_pipe);
	while (pid_info.pipe_i--)
		waitpid(pid_info.pid[i++], &errno, 0);
	// if (!fd_pipe->pipe_size)
		// close_redirect(ats->token);
	free(fd_pipe->fd);
	free(fd_pipe);
	free(pid_info.pid);
}

void	run_cmd(char *line, char **envp)
{
	t_ats		*ats;
	t_token		*token;
	t_pipe_fd	*fd_pipe;
	t_pid_info 	pid_info;

	struct_init(ats, token, fd_pipe, &pid_info);
	token = tokenize(line);
	if (!syntax_check(token))
		return ;
	expansion(token);
	redirect_open(token);
	ats = parser(token);
	make_child(ats, envp, fd_pipe, pid_info);
	free_ats(ats);
}

t_env		*g_env = NULL;
int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_pid_info	pid_info;

	errno = 0; // エラー番号をリセット
	register_signal();
	rl_outstream = stderr;
	init_env(envp);
	// print_env();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			handle_eof(line);
		else
		{
			add_history(line);
			run_cmd(line, envp);
			free(line);
		}
	}
	return (WEXITSTATUS(errno));
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
