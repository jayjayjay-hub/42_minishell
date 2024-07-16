#include "minishell.h"

// eofが来た場合の処理
void	handle_eof(char *line)
{
	write(2, "exit\n", 5);
	if (line)
		free(line);
	exit(WEXITSTATUS(errno));
}

void	struct_init(t_cmd *cmd, char **envp)
{
	cmd->envp = envp;
	cmd->ats = NULL;
	cmd->fd_pipe = NULL;
	cmd->pid_info.pid = NULL;
	cmd->pid_info.pipe_i = 0;
}

void	make_child(t_cmd *command, t_env *env)
{
	int i;
	t_ats *tmp;

	i = 0;
	tmp = command->ats;
	command->fd_pipe = create_pipe(command->ats);
	command->pid_info.pid = (pid_t *)malloc(sizeof(pid_t) * (command->fd_pipe->pipe_size + 1));
	while (command->ats)
	{
		if (add_variable(command->ats->token, &env))
		{
			// variable_list_print();
			command->ats = command->ats->next;
			continue ;
		}
		if (!command->fd_pipe->pipe_size && builtin_control(command->ats->token, &env))
		{
			command->ats = command->ats->next;
			continue ;
		}
		command->pid_info.pid[command->pid_info.pipe_i] = child(command, env);
		command->pid_info.pipe_i++;
		command->ats = command->ats->next;
	}
	close_pipe(command->fd_pipe);
	while (command->pid_info.pipe_i--)
	{
		waitpid(command->pid_info.pid[i++], &errno, 0);
		error_status(errno);
	}
	if (!command->fd_pipe->pipe_size && builtin_check(tmp->token))
		close_redirect(tmp->token);
}

void	run_cmd(char *line, char **envp, t_env *env)
{
	t_cmd		*command;
	t_token		*token;

	token = NULL;
	command = (t_cmd *)malloc(sizeof(t_cmd));
	struct_init(command, envp);
	token = tokenize(line);
	if (!syntax_check(token))
		return ;
	expansion(token, env);
	redirect_open(token);
	command->ats = parser(token);
	make_child(command, env);
	free_command(command);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_env		*env;

	register_signal();
	rl_outstream = stderr;
	env = NULL;
	env = init_env(envp);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			handle_eof(line);
		else
		{
			add_history(line);
			run_cmd(line, envp, env);
			free(line);
		}
	}
	return (errno);
}

int	error_status(int error_code)
{
	static int status;

	if (error_code < 0)
		return (WEXITSTATUS(status));
	status = error_code;
	return (WEXITSTATUS(status));
}

// valgrind --leak-check=full -s ./minishell
