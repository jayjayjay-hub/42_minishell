#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

// exit status
# define CMD_NOT_FOUND	127

typedef enum e_token_type
{
	WORD,
	OP,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	MY_EOF,
}	t_token_type;
typedef struct s_token
{
	char			*str;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

// main.c
void	ft_error(void);

// tokenizer.c
t_token *tokenize(char *line);
t_token	*new_token_(char *str, t_token_type type);
void	add_back(t_token **list, t_token *new);
void	free_token(t_token *token);

#endif
