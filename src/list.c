#include "minishell.h"

// list.c

/*
typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	MY_EOF,
}	t_token_type;
typedef struct s_token
{
	char			*str;
	t_token_type	type;
	struct s_token	*next;
}	t_token;
*/

// add front
void	add_front(t_token **list, t_token *new)
{
	if (!list || !new)
		return ;
	new->next = *list;
	*list = new;
}

// add back
void	add_back(t_token **list, t_token *new)
{
	if (!list || !new)
		return ;
	if (*list)
		list_last(*list)->next = new;
	else
		*list = new;
}

t_token *list_last(t_token *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

t_token	*new_token(char *str, t_token_type type)
{
	t_token	*ret;

	ret = (t_token *)malloc(sizeof(t_token));
	if (!ret)
		ft_error();
	ret->str = str;
	ret->type = type;
	return (ret);
}

void	new_add_back(t_token **head, char *str, t_token_type type)
{
	t_token	*new;

	new = new_token(str, type);
	add_back(head, new);
}
