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

# ifdef __linux__
// 俺のUbuntu環境だと必要でした
#  include <sys/wait.h>
#  define S_IREAD S_IRUSR
#  define S_IWRITE S_IWUSR
# endif

# ifdef __APPLE__
	void	rl_replace_line(const char *, int);
	void	rl_on_new_line(void);
#endif

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

// exit status
# define CMD_NOT_FOUND	127

// signal
typedef struct sigaction	t_sig;

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

typedef struct s_ats
{
	t_token			*token;
	struct s_ats	*next;
}	t_ats;

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

// redirect.c
void	redirect(t_token **token);

// parser.c
t_ats	*parser(t_token *token);

// ats_list.c
void	add_back_ats(t_ats **list, t_ats *new);
void	free_ats(t_ats *ats);
int		ats_list_size(t_ats *ats);
void	print_ats(t_ats *ats);
t_ats	*new_ats(t_token *token);

#endif
