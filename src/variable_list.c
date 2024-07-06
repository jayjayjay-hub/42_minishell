#include "minishell.h"

/*
typedef struct s_variable
{
	char			*key;
	char			*value;
	struct s_variable	*next;
}	t_variable;
*/

void	variable_list_add_back(t_variable **lst, t_variable *new)
{
	t_variable	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
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

void	variable_list_free(t_variable *lst)
{
	t_variable	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->key);
		free(lst->value);
		free(lst);
		lst = tmp;
	}
}

void	variable_list_print(t_variable *lst)
{
	while (lst)
	{
		printf("key: %s, value: %s\n", lst->key, lst->value);
		lst = lst->next;
	}
}
