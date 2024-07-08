
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
	int	len;

	len = 0;
	while (line[len] && !is_metachar(line[len]))
	{
		if (is_single_quote(line[len]))
		{
			len++;
			while (line[len] && !is_single_quote(line[len]))
				len++;
			if (!line[len])
			{
				printf("single quote error\n");
				return (-1);
			}
		}
		else if (is_double_quote(line[len]))
		{
			len++;
			while (line[len] && !is_double_quote(line[len]))
				len++;
			if (!line[len])
			{
				printf("doble quote error\n");
				return (-1);
			}
		}
		len++;
	}
	return (len);
}

bool	single_quote(char **line, char **word, int *word_len)
{
	(*word)[*word_len] = **line;
	(*word_len)++;
	(*line)++;
	while (**line && !is_single_quote(**line))
	{
		(*word)[*word_len] = **line;
		(*word_len)++;
		(*line)++;
	}
	(*word)[*word_len] = **line;
	(*word_len)++;
	(*line)++;
	return (true);
}

bool	double_quote(char **line, char **word, int *word_len)
{
	(*word)[*word_len] = **line;
	(*word_len)++;
	(*line)++;
	while (**line && !is_double_quote(**line))
	{
		(*word)[*word_len] = **line;
		(*word_len)++;
		(*line)++;
	}
	(*word)[*word_len] = **line;
	(*word_len)++;
	(*line)++;
	return (true);
}

char *get_word(char *line)
{
	char	*word;
	int		word_len;

	word_len = get_word_len(line);
	if (word_len == -1)
		return (NULL);
	word = ft_calloc(1, word_len + 1); // word_lenを実装する
	word_len = 0;
	while (*line && !is_metachar(*line))
	{
		if (is_single_quote(*line))
			single_quote(&line, &word, &word_len);
		else if (is_double_quote(*line))
			double_quote(&line, &word, &word_len);
		else
			word[word_len++] = *line++;
	}
	// null文字を追加
	word[word_len] = '\0';
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
		if (!*line || *line == '#')
			break ;
		type = check_type(line); // トークンの種類をチェック
		token_len = add_token(&token, line, type); // トークンを取得
		if (!token_len)
		{
			free_token(token);
			*status = 258;
			return (NULL);
		}
		line += token_len; // トークンの長さ分だけlineを進める
		debug++;
		if (debug > 2)
			break ;
	}
	// print_token(token);
	return (token);
}
