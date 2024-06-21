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
		ft_error();
	token->str = str;
	if (!token->str)
	{
		perror("Failed to duplicate string");
		free(token);
		exit(EXIT_FAILURE);
	}
	token->type = type;
	token->next = NULL;
	return token;
}

void	free_token(t_token *token)
{
	t_token *tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->str);
		free(tmp);
	}
}
