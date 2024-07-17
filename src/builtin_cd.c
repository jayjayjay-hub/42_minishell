#include "minishell.h"

// builtin_cd.c

bool	do_cd(t_token *token, t_env **env, char *path)
{
	if (token->next)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		error_status(256 * 1);
		return (false);
	}
	if (!ft_strncmp(token->str, "-", 1) && ft_strlen(token->str) == 1)
	{
		path = get_env_value("OLDPWD", *env);
		ft_putendl_fd(path, 1);
	}
	else if (!ft_strncmp(token->str, "~", 1) && ft_strlen(token->str) == 1)
		path = get_env_value("HOME", *env);
	else
		path = ft_strdup(token->str);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		perror(path);
		error_status(256 * 1);
		free(path);
		return (false);
	}
	return (true);
}

bool	builtin_cd(t_token *token, t_env **env)
{
	char	*path;

	if (!token->next)
	{
		path = get_env_value("HOME", *env);
		if (!path)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			free(path);
			return (false);
		}
		if (chdir(path) == -1)
		{
			ft_putstr_fd("cd: ", 2);
			perror(path);
			error_status(256 * 1);
			return (false);
		}
		return (true);
	}
	token = token->next;
	return (do_cd(token, env, path));
}
