#include "minishell.h"

void	init_env(char **envp)
{
	int		i;
	t_env	*new;
	t_env	*tmp;

	i = 0;
	while (envp[i])
	{
		new = new_env(envp[i]);
		add_back_env(new);
		i++;
	}
}
