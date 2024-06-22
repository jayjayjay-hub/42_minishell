#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

// exit status
# define CMD_NOT_FOUND	127

// signal
typedef struct sigaction	t_sig;

// define token type str
# define TYPE_NUM 5
# define PIPE_STR "|"
# define REDIRECT_IN_STR "<"
# define REDIRECT_OUT_STR ">"
# define REDIRECT_HERE_DOC_STR "<<"
# define REDIRECT_APPEND_STR ">>"

typedef enum e_token_type
{
	WORD,
	PIPE, // |
	REDIRECT_IN, // <
	REDIRECT_OUT, // >
	REDIRECT_HERE_DOC, // <<
	REDIRECT_APPEND, // >>
}	t_token_type;
typedef struct s_token
{
	char			*str;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

// main.c

// tokenizer.c
t_token *tokenize(char *line);

// list.c
t_token	*new_token(char *str, t_token_type type);
void		add_back(t_token **list, t_token *new);
void		free_token(t_token *token);
int			token_list_size(t_token *token);
void		print_token(t_token *token);

// signal.c
void	register_signal(void);
void	signal_handler(int signum);

// error.c
void	ft_error(char *cmd, char *target, char *main_message, int status);

#endif
