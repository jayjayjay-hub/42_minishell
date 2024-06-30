// parse_tree_list.c

/*
typedef struct s_parse_tree
{
	t_token			*token;
	struct s_parse_tree	*left;
	struct s_parse_tree	*right;
}	t_parse_tree;
*/

#include "minishell.h"

t_parse_tree	*new_parse_tree(t_token *token, int token_count, bool is_parse)
{
	t_parse_tree	*new;
	t_token			*tmp;

	new = (t_parse_tree *)malloc(sizeof(t_parse_tree));
	if (!new)
		ft_error(NULL, NULL, "malloc failed", 1);
	tmp = NULL;
	if (is_parse)
	{
		while (token_count > 0)
		{
			add_back(&tmp, new_token(token->str, token->type));
			token = token->next;
			token_count--;
		}
		new->token = tmp;
	}
	else
		new->token = token;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

void	add_back_parse_tree(t_parse_tree **list, t_parse_tree *new)
{
	t_parse_tree	*tmp;

	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->right)
		tmp = tmp->right;
	tmp->right = new;
}

void	free_parse_tree(t_parse_tree *parse_tree)
{
	t_parse_tree	*tmp;

	while (parse_tree)
	{
		tmp = parse_tree->right;
		free_token(parse_tree->token);
		free(parse_tree);
		parse_tree = tmp;
	}
}
