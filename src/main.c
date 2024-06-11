#include "minishell.h"

void	ft_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

void	dp_free(char **arg)
{
	int	i;

	i = -1;
	while (arg[++i])
		free(arg[i]);
	free(arg);
}

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
	ft_error();
	return (NULL);
}

void	do_execve(char *line, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(line, ' ');
	if (!cmd[0])
		ft_error();
	if (!ft_strncmp(cmd[0], "/", 1))
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

void	child(char *line, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error();
	if (pid == 0)
		do_execve(line, envp);
	waitpid(pid, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL || (!ft_strncmp(line, "exit", 4)))
			break ;
		if (*line)
		{
			add_history(line);
			child(line, envp);
			free(line);
		}
	}
	exit(0);
}
