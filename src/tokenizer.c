
#include "minishell.h"

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

int	get_word_len(char *line)
{
	int		len;
	char	quote;

	len = 0;
	while (line[len] && !is_metachar(line[len]))
	{
		if (is_quote(line[len]))
		{
			quote = line[len];
			len++;
			while (line[len] && line[len] != quote)
				len++;
			if (!line[len])
			{
				printf("minishell: quote not closed\n");
				return (-1);
			}
			len++;
		}
		else
			len++;
	}
	return (len);
}

char *get_word(char *line)
{
	char	*word;
	int		word_len;
	char	quote;

	word_len = get_word_len(line);
	if (word_len == -1)
		return (NULL);
	word = ft_calloc(1, word_len + 1); // null文字分を確保
	word_len = 0;
	while (line[word_len] && !is_metachar(line[word_len]))
	{
		if (is_quote(line[word_len]))
		{
			quote = line[word_len];
			word[word_len] = line[word_len];
			word_len++;
			while (line[word_len] && line[word_len] != quote)
			{
				word[word_len] = line[word_len];
				word_len++;
			}
			word[word_len] = line[word_len];
			word_len++;
		}
		else
		{
			word[word_len] = line[word_len];
			word_len++;
		}
	}
	word[word_len] = '\0'; // null文字を追加
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
	if (!token_str)
		return (0);
	new = new_token(token_str, type);
	add_back(token, new);
	return (strlen(token_str));
}

t_token *tokenize(char *line, int *status)
{
	t_token			*token;
	t_token_type	type;
	int				token_len;

	token = NULL;
	int debug = 0;
	while (*line)
	{
		line = pass_space(line); // スペースを飛ばす
		if (!*line || *line == '#') // 空文字かコメント行なら終了
			break ;
		type = check_type(line); // トークンの種類をチェック
		token_len = add_token(&token, line, type); // トークンを取得
		if (!token_len) // トークンの取得に失敗したらエラー
		{
			free_token(token);
			*status = 258;
			return (NULL);
		}
		line += token_len; // トークンの長さ分だけlineを進める
	}
	// print_token(token);
	return (token);
}
