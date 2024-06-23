#include "minishell.h"

/*
typedef struct s_ats
{
	t_token			*token;
	struct s_ats	*next;
}	t_ats;
*/

void	add_back_ats(t_ats **list, t_ats *new)
{
	t_ats	*tmp;

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

t_ats	*new_ats(t_token *token)
{
	t_ats	*ats;
	t_token	*tmp;

	ats = malloc(sizeof(t_ats));
	if (!ats)
		ft_error("malloc", "ats", strerror(errno), EXIT_FAILURE);
	tmp = NULL;
	// Pipeまでのトークンをats->tokenに追加
	while (token && token->type != PIPE)
	{
		add_back(&tmp, new_token(token->str, token->type));
		token = token->next;
	}
	if (tmp)
	{
		ats->token = tmp;
		ats->next = NULL;
	}
	else
	{
		free(ats);
		ats = NULL;
	}
	return ats;
}

void	free_ats(t_ats *ats)
{
	t_ats	*tmp;

	while (ats)
	{
		tmp = ats->next;
		free_token(ats->token);
		free(ats);
		ats = tmp;
	}
}

int	ats_list_size(t_ats *ats)
{
	int		size;

	size = 0;
	while (ats)
	{
		size++;
		ats = ats->next;
	}
	return size;
}

void	print_ats(t_ats *ats)
{
	int debug = 0;

	printf("<< ats list >>\n\n");
	while (ats)
	{
		printf("<< ats[%d] >>\n", debug);
		print_token(ats->token);
		printf("\n");
		ats = ats->next;
		if (debug++ > 10)
			break ;
	}
	printf("<< ats list end >>\n");
}
