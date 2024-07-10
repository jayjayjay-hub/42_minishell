#include "minishell.h"

// builtin_cd.c

bool	builtin_cd(t_token *token)
{
	char	*path;

	if (!token->next)
	{
		path = get_env_value("HOME");
		if (!path)
		{
			write(2, "cd: HOME not set\n", 17);
			g_status = 1;
			free(path);
			return (false);
		}
		if (chdir(path) == -1)
		{
			write(2, "cd: ", 4);
			perror(path);
			g_status = 1;
			return (false);
		}
		return (true);
	}
	token = token->next;
	if (token->next)
	{
		write(2, "cd: too many arguments\n", 24);
		g_status = 256 * 1;
		return (false);
	}
	path = strdup(token->str);
	if (chdir(path) == -1)
	{
		write(2, "cd: ", 4);
		perror(path);
		g_status = 1;
		free(path);
		return (false);
	}
	return (true);
}
