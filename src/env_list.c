#include "minishell.h"

/*
typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env	*next;
}	t_env;

extern t_env	*env;
g_envはmain.cで定義
*/

void	add_back_env(t_env *new)
{
	t_env	*tmp;

	if (!new)
		return ;
	if (!g_env)
		g_env = new;
	else
	{
		tmp = g_env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

char *get_env_key_from_envp(char *env_line)
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

char *get_env_value_from_envp(char *env_line)
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

t_env	*new_env(char *env_line)
{
	t_env	*env;
	char	*key;
	char	*value;

	env = malloc(sizeof(t_env));
	if (!env)
		ft_error("malloc", "env", strerror(errno), EXIT_FAILURE);
	key = get_env_key_from_envp(env_line);
	value = get_env_value_from_envp(env_line);
	env->key = key;
	env->value = value;
	env->next = NULL;
	return (env);
}

void	export_env(char *key, char *value)
{
	t_env	*tmp;
	char *tmp_value;
	char *key_value;

	tmp = g_env;
	if (!value)
	{
		value = get_variable_value(key);
		if (!value)
			return ;
	}
	while (tmp)
	{
		if (strlen(tmp->key) == strlen(key) && !ft_strncmp(tmp->key, key, strlen(key)))
		{
			tmp_value = tmp->value;
			tmp->value = strdup(value);
			free(tmp_value);
			return ;
		}
		tmp = tmp->next;
	}
	key_value = ft_strjoin(key, ft_strjoin("=", value));
	add_back_env(new_env(key_value));
}

char	*get_env_value(char *key)
{
	t_env	*tmp;
	int		key_len;

	tmp = g_env;
	key_len = ft_strlen(key);
	while (tmp)
	{
		if (strlen(tmp->key) == key_len && !ft_strncmp(tmp->key, key, key_len))
			return (strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

void	free_env(void)
{
	t_env	*tmp;

	while (g_env)
	{
		tmp = g_env->next;
		free(g_env->key);
		free(g_env->value);
		free(g_env);
		g_env = tmp;
	}
}

void	print_export_env(void) // exportで表示するときに使う
{
	t_env	*tmp;

	tmp = g_env;
	while (tmp)
	{
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	print_env(void) // envで表示するときに使う
{
	t_env	*tmp;

	tmp = g_env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

int	env_list_size(void)
{
	int		size;
	t_env	*tmp;

	size = 0;
	tmp = g_env;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}