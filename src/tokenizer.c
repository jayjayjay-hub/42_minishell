
#include "minishell.h"

int is_metachar(char c)
{
	return (c && ft_strchr("()<>", c));
}

int	is_quote(char c)
{
	return (c && ft_strchr("'\"", c));
}

int	is_word(const char *s)
{
	return (*s && !is_metachar(*s));
}

t_token_type	check_type(char *line)
{
	// t_token_type	type;
	if (ft_strncmp(line, "|", 1) == 0)
		return (PIPE);
	else if (ft_strncmp(line, "<<", 2) == 0)
		return (REDIRECT_HERE_DOC);
	else if (ft_strncmp(line, ">>", 2) == 0)
		return (REDIRECT_APPEND);
	else if (ft_strncmp(line, "<", 1) == 0)
		return (REDIRECT_IN);
	else if (ft_strncmp(line, ">", 1) == 0)
		return (REDIRECT_OUT);
	else
		return (WORD);
}

t_token *word(char *line, int *quote)
{
	char	*word;
	int		len;
	char	quote_char;

	len = 0;
	word = ft_calloc(1, ft_strlen(line) + 1);
	while (*line && !is_metachar(*line) && !ft_isspace(*line))
	{
		if (is_quote(*line))
		{
			quote_char = *line;
			*quote += 2;
			line++;
			while (*line && *line != quote_char)
				word[len++] = *line++;
			if (*line != quote_char)
				ft_error(NULL, NULL, "quote not closed", 1);
			line++;
		}
		else
			word[len++] = *line++;
	}
	word[len] = '\0';
	return (new_token(word, WORD));
}

t_token	*operator(char *line, t_token_type type)
{
	if (type == PIPE)
		return (new_token("|\0", PIPE));
	else if (type == REDIRECT_HERE_DOC)
		return (new_token("<<\0", REDIRECT_HERE_DOC));
	else if (type == REDIRECT_APPEND)
		return (new_token(">>\0", REDIRECT_APPEND));
	else if (type == REDIRECT_IN)
		return (new_token("<\0", REDIRECT_IN));
	else if (type == REDIRECT_OUT)
		return (new_token(">\0", REDIRECT_OUT));
	else
		return (NULL);
}

int	get_token(t_token **token, char *line, t_token_type type)
{
	t_token	*new_token;
	char		*rest;
	int			quote_count;

	quote_count = 0;
	if (type == WORD)
		new_token = word(line, &quote_count);
	else
		new_token = operator(line, type);
	add_back(token, new_token);
	return (ft_strlen(new_token->str) + quote_count);
}

t_token *tokenize(char *line)
{
	t_token *token;
	int			token_len;
	t_token_type	type;

	token = NULL;
	while (*line)
	{
		line = pass_space(line);
		if (!*line)
			break ;
		type = check_type(line);
		token_len = get_token(&token, line, type);
		line += token_len;
	}
	// print_token(token);
	return (token);
}
