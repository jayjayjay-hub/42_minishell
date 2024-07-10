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

char *get_env_key(char *env_line)
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

char *get_env_value(char *env_line)
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

t_env	*new_env(char *env_line) // env_line ex) HOME=/home/jtakahas
{
	t_env	*env;
	char	*key;
	char	*value;

	env = malloc(sizeof(t_env));
	if (!env)
		ft_error("malloc", "env", strerror(errno), EXIT_FAILURE);
	key = get_env_key(env_line);
	value = get_env_value(env_line);
	env->key = key;
	env->value = value;
	env->next = NULL;
	return (env);
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

void	print_env(void)
{
	t_env	*tmp;

	tmp = g_env;
	printf("<< env list >>\n\n");
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
