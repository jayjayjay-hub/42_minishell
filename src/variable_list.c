#include "minishell.h"

/*
typedef struct s_variable
{
	char			*key;
	char			*value;
	struct s_variable	*next;
}	t_variable;

// global variable
t_variable	*variable;
*/

void	variable_list_add_back(t_variable *new)
{
	t_variable	*tmp;

	if (!variable)
	{
		variable = new;
		return ;
	}
	tmp = variable;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_variable	*variable_list_new(char *key, char *value)
{
	t_variable	*new;

	new = (t_variable *)malloc(sizeof(t_variable));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	variable_list_free(void)
{
	t_variable	*tmp;

	while (variable)
	{
		tmp = variable->next;
		free(variable->key);
		free(variable->value);
		free(variable);
		variable = tmp;
	}
}

char	*get_variable_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	if (!is_al_under(str[i]))
		return (NULL);
	i++;
	while (str[i] && is_alnum_under(str[i]))
		i++;
	key = ft_substr(str, 0, i);
	return (key);
}

char	*get_variable_value(char *key)
{
	t_variable	*tmp;

	tmp = variable;
	if (!key)
		return (NULL);
	while (tmp)
	{
		if (!strcmp(tmp->key, key))
			return (strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

void	variable_list_print(void)
{
	t_variable	*tmp;

	tmp = variable;
	while (tmp)
	{
		printf("key = %s, value = %s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
