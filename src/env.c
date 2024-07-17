#include "minishell.h"

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
