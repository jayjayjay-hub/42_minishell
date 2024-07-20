#include "minishell.h"

char	*get_key_from_envp(char *env_line)
{
	int		i;
	char	*key;

	i = 0;
	while (env_line[i] && env_line[i] != '=')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		ft_error("malloc", "key", strerror(errno), EXIT_FAILURE);
	ft_strlcpy(key, env_line, i + 1);
	return (key);
}

char	*get_value_from_envp(char *env_line)
{
	int		i;
	char	*value;

	i = 0;
	while (env_line[i] && env_line[i] != '=')
		i++;
	if (!env_line[i])
		return (NULL);
	value = ft_strdup(env_line + i + 1);
	if (!value)
		ft_error("ft_strdup", "value", strerror(errno), EXIT_FAILURE);
	return (value);
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = NULL;
	i = 0;
	env = NULL;
	while (envp[i])
	{
		new = new_export_env(envp[i]);
		env_add_back(new, &env);
		i++;
	}
	return (env);
}
