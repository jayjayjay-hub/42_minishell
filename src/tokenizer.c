
#include "minishell.h"

int is_metachar(char c)
{
	return (c && ft_strchr("|&;()<> \t\n", c));
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

t_token *word(char *line)
{
	const char	*start;
	char		*word;

	start = line;
	while (*line && !is_metachar(*line))
		line++;
	word = strndup(start, line - start);
	if (!word)
		ft_error();
	return (new_token(word, WORD));
}

t_token	*operator(char *line)
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
			return (new_token(op, OP));
		}
		i++;
	}
	ft_error();
	return (NULL);
}

int	get_token(t_token **token, char *line, t_token_type type)
{
	t_token	*new_token;
	char	*rest;

	if (type == WORD)
		new_token = word(line);
	else if (type == OP)
		new_token = operator(line);
	add_back(token, new_token);
	return (ft_strlen(new_token->str));
}

t_token *tokenize(char *line)
{
	t_token *token = NULL;
	int	token_len;

	while (*line)
	{
		line = pass_space(line);
		if (is_operator(line))
			token_len = get_token(&token, line, OP);
		else if (is_word(line))
			token_len = get_token(&token, line, WORD);
		else
			ft_error();
		line += token_len;
	}
	return (token);
}
