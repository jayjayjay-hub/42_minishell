
#include "minishell.h"

int is_metachar(char c)
{
	return (c && ft_strchr("|&;()<> \t\n", c));
}

int	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

t_token *new_token(char *str, t_token_type type)
{
	t_token *ret;

	ret = ft_calloc(1, sizeof(t_token));
	if (!ret)
		ft_error();
	ret->str = str;
	ret->type = type;
	return (ret);
}

int	consume_blank(char **rest, char *line)
{
	if (is_blank(*line))
	{
		while (*line && is_blank(*line))
			line++;
		*rest = line;
		return (1);
	}
	*rest = line;
	return (0);
}

t_token *word(char **ret, char *line)
{
	const char	*start;
	char		*word;

	while (*line && !is_metachar(*line))
		line++;
	word = strndup(start, line - start);
	if (!word)
		ft_error();
	*ret = line;
	return (new_token(word, WORD));
}

// debug用
void print_token(t_token *token)
{
	while (token)
	{
		ft_printf("str: %s, type: %d\n", token->str, token->type);
		token = token->next;
	}
}

t_token *tokenize(char *line)
{
	t_token head;
	t_token *current;

	head.next = NULL;
	current = &head;
	printf("line: %s\n", line);
	while (*line)
	{
		printf("line: %c\n", *line);
		if (consume_blank(&line, line))
			continue ;
		else
			current->next = word(&line, line);
		current = current->next;
		line++;
	}
	current->next = new_token(NULL, MY_EOF);
	print_token(head.next);
	return (head.next);
}
