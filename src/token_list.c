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

void	add_back(t_token **list, t_token *new)
{
	t_token	*tmp;

	if (!list || !new)
		return ;
	if (*list == NULL)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_token	*new_token(char *str, t_token_type type)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		ft_error("malloc", "token", strerror(errno), EXIT_FAILURE);
	if (type != WORD)
	{
		token->str = strdup(str);
		if (!token->str)
			ft_error("ft_strdup", "token->str", strerror(errno), EXIT_FAILURE);
	}
	else
		token->str = str;
	token->type = type;
	token->next = NULL;
	return token;
}

int	token_list_size(t_token *token)
{
	long long		size;

	size = 0;
	while (token)
	{
		if (size == INT_MAX)
			return (-1);
		size++;
		token = token->next;
	}
	return size;
}

void	free_token(t_token *token)
{
	t_token *tmp;

	tmp = token;
	if (!tmp)
		return ;
	while (tmp->next)
	{
		free(tmp->str);
		free(tmp);
		tmp = tmp->next;
	}
}

void	print_token(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while (tmp)
	{
		printf("str: %s, type: %d\n", tmp->str, tmp->type);
		tmp = tmp->next;
	}
}
