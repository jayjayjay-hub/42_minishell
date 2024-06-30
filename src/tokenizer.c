
#include "minishell.h"

int is_metachar(char c)
{
	return (c && ft_strchr("&|<>()", c));
}

int	is_quote(char c)
{
	return (c && ft_strchr("'\"", c));
}

t_token_type	check_type(char *line)
{
	// t_token_type	type;
	if (strncmp(line, "|", 1) == 0)
		return (PIPE);
	else if (strncmp(line, "<<", 2) == 0)
		return (REDIRECT_HERE_DOC);
	else if (strncmp(line, ">>", 2) == 0)
		return (REDIRECT_APPEND);
	else if (strncmp(line, "<", 1) == 0)
		return (REDIRECT_IN);
	else if (strncmp(line, ">", 1) == 0)
		return (REDIRECT_OUT);
	else if (strncmp(line, "(", 1) == 0)
		return (BRACKET_LEFT);
	else if (strncmp(line, ")", 1) == 0)
		return (BRACKET_RIGHT);
	else
		return (WORD);
}

int	word_len(char *line)
{
	int		len;
	char	quote_char;

	len = 0;
	while (*line && !is_metachar(*line) && !ft_isspace(*line))
	{
		if (is_quote(*line))
		{
			quote_char = *line;
			line++;
			while (*line && *line != quote_char)
			{
				len++;
				line++;
			}
			if (*line != quote_char)
				ft_error(NULL, NULL, "quote not closed", 1);
		}
		else
			len++;
		line++;
	}
	return (len);
}

char *get_word(char *line)
{
	char	*word;
	int		len;
	char	quote_char;

	len = 0;
	word = ft_calloc(1, word_len(line) + 1);
	while (*line && !is_metachar(*line) && !ft_isspace(*line))
	{
		if (is_quote(*line))
		{
			quote_char = *line;
			word[len++] = *line++;
			while (*line && *line != quote_char)
				word[len++] = *line++;
			if (*line != quote_char)
				ft_error(NULL, NULL, "quote not closed", 1);
			word[len++] = *line++;
		}
		else
			word[len++] = *line++;
	}
	word[len] = '\0';
	return (word);
}

char	*get_operator(char *line, t_token_type type)
{
	char	*operator;
	int		len;

	len = 1;
	if (type == REDIRECT_HERE_DOC || type == REDIRECT_APPEND)
		len = 2;
	operator = ft_calloc(1, len + 1);
	ft_strlcpy(operator, line, len + 1);
	return (operator);
}

int	add_token(t_token **token, char *line, t_token_type type)
{
	t_token		*new;
	char 		*token_str;
	char 		*rest;

	if (type == WORD)
		token_str = get_word(line);
	else
		token_str = get_operator(line, type);
	new = new_token(token_str, type);
	add_back(token, new);
	return (strlen(token_str));
}

t_token *tokenize(char *line)
{
	t_token			*token;
	t_token_type	type;
	int				token_len;

	token = NULL;
	while (*line)
	{
		line = pass_space(line); // スペースを飛ばす
		if (!*line) // 空白行だったら終了
			break ;
		type = check_type(line); // トークンの種類をチェック
		token_len = add_token(&token, line, type); // トークンを取得
		line += token_len; // トークンの長さ分だけlineを進める
	}
	print_token(token);
	return (token);
}
