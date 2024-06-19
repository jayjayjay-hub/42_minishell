
#include "minishell.h"

int is_metachar(char c)
{
	return (c && ft_strchr("|&;()<> \t\n", c));
}

int	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_word(const char *s)
{
	return (*s && !is_metachar(*s));
}

int	is_operator(const char *s)
{
	static char	*const operators[] = {"||", "&", "&&", ";", ";;", "(", ")", "|", "\n"};
	size_t				i = 0;				

	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (ft_memcmp(s, operators[i], ft_strlen(operators[i])) == 0)
			return (1);
		i++;
	}
	return (0);
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

	start = line;
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

t_token	*operator(char **rest, char *line)
{
	static char	*const	operators[] = {"||", "&", "&&", ";", ";;", "(", ")", "|", "\n"};
	size_t				i = 0;				
	char				*op;

	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (ft_memcmp(line, operators[i], ft_strlen(operators[i])) == 0)
		{
			op = strdup(operators[i]);
			if (op == NULL)
				ft_error();
			*rest = line + strlen(op);
			return (new_token(op, OP));
		}
		i++;
	}
	ft_error();
	return (NULL);
}

t_token *tokenize(char *line)
{
	t_token head;
	t_token *current;

	head.next = NULL;
	current = &head;
	while (*line)
	{
		if (consume_blank(&line, line))
			continue ;
		else if (is_operator(line))
			current->next = operator(&line, line);
		else if (is_word(line))
			current->next = word(&line, line);
		else
			ft_error();
		current = current->next;
		if (*line)
			line++;
	}
	current->next = new_token(NULL, MY_EOF);
	print_token(head.next);
	return (head.next);
}
