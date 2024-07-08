
#include "minishell.h"

t_token_type	check_type(char *line)
{
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

char	*get_word(char *line)
{
	char	*word;
	int		word_len;
	char	quote;

	word_len = get_word_len(line);
	if (word_len == -1)
		return (NULL);
	word = ft_substr(line, 0, word_len);
	if (!word)
	{
		printf("minishell: malloc failed\n");
		return (NULL);
	}
	return (word);
}

char	*get_operator(char *line, t_token_type type)
{
	char	*operator;
	int		len;

	len = 1;
	if (type == REDIRECT_HERE_DOC || type == REDIRECT_APPEND)
		len = 2;
	operator = ft_substr(line, 0, len);
	if (!operator)
	{
		printf("minishell: malloc failed\n");
		return (NULL);
	}
	return (operator);
}

int	add_token(t_token **token, char *line, t_token_type type)
{
	t_token		*new;
	char		*token_str;
	char		*rest;

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

t_token	*tokenize(char *line, int *status)
{
	t_token			*token;
	t_token_type	type;
	int				token_len;

	token = NULL;
	while (*line)
	{
		line = pass_space(line);
		if (!*line || *line == '#')
			break ;
		type = check_type(line);
		token_len = add_token(&token, line, type);
		if (!token_len)
		{
			free_token(token);
			*status = 258;
			return (NULL);
		}
		line += token_len;
	}
	// print_token(token);
	return (token);
}
