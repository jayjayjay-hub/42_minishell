#include "minishell.h"

int	get_pipe_count(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == PIPE)
			count++;
		token = token->next;
	}
	return (count);
}

t_ats	*parser(t_token *token)
{
	t_ats	*ats;
	t_ats	*new;

	ats = NULL;
	while (token)
	{
		if (token && token->type == PIPE)
			token = token->next;
		new = new_ats(token);
		if (!new)
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return (NULL);
		}
		add_back_ats(&ats, new);
		while (token && token->type != PIPE)
			token = token->next;
	}
	// debug
	// print_ats(ats);
	return (ats);
}
