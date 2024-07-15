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
			ft_putendl_fd("cd: HOME not set", 2);
			g_status = 1;
			free(path);
			return (false);
		}
		if (chdir(path) == -1)
		{
			ft_putstr_fd("cd: ", 2);
			perror(path);
			g_status = 1;
			return (false);
		}
		return (true);
	}
	token = token->next;
	if (token->next)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		g_status = 256 * 1;
		return (false);
	}
	if (ft_strncmp(token->str, "-", 1) == 0)
	{
		path = get_env_value("OLDPWD");
		ft_putendl_fd(path, 1);
	}
	else if (ft_strncmp(token->str, "~", 1) == 0)
		path = get_env_value("HOME");
	else
		path = ft_strdup(token->str);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		perror(path);
		g_status = 1;
		free(path);
		return (false);
	}
	return (true);
}
