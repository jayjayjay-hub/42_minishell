#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <signal.h>

# ifdef __linux__
// 俺のUbuntu環境だと必要でした
#  include <sys/wait.h>
#  define S_IREAD S_IRUSR
#  define S_IWRITE S_IWUSR
# endif

// # ifdef __APPLE__
// 	void	rl_replace_line(const char *, int);
// 	void	rl_on_new_line(void);
// #endif

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

// exit status
# define CMD_NOT_FOUND	127

// here_doc
# define HEREDOC "/tmp/.heredoc_tmp"

// signal
typedef struct sigaction	t_sig;

extern int	g_status;

typedef struct s_key_value
{
	char	*key;
	char	*value;
}	t_key_value;

typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env	*next;
}	t_env;

extern t_env	*g_env;

typedef enum e_token_type
{
	WORD,
	PIPE, // |
	REDIRECT_IN, // <
	REDIRECT_OUT, // >
	REDIRECT_HERE_DOC, // <<
	REDIRECT_APPEND, // >>
	BRACKET_LEFT, // (
	BRACKET_RIGHT, // )
}	t_token_type;

typedef enum e_variable_type
{
	STRING,
	ARRAY,
}	t_variable_type;

typedef struct s_token
{
	char			*str;
	t_token_type	type;
	int 			fd;
	int				backup_fd;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_variable
{
	char			*key;
	char			*value;
	struct s_variable	*next;
}	t_variable;

extern t_variable	*variable;

typedef struct s_parse_tree
{
	t_token			*token;
	struct s_parse_tree	*left;
	struct s_parse_tree	*right;
}	t_parse_tree;

typedef struct s_ats
{
	t_token			*token;
	struct s_ats	*next;
	struct s_ats	*prev;
}	t_ats;

typedef struct pipe_fd
{
	int	*fd;
	int	pipe_size;
}	t_pipe_fd;

typedef struct pid_info
{
	pid_t	*pid;
	int		pipe_i;
}	t_pid_info;


// main.c

// tokenizer.c
t_token *tokenize(char *line);

// list.c
t_token	*new_token(char *str,
					t_token_type type,
					int fd);
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
void	redirect_open(t_token *token);
void	close_redirect(t_token *token);

// parser.c
int	get_pipe_count(t_token *token);
t_ats	*parser(t_token *token);

// ats_list.c
void	add_back_ats(t_ats **list, t_ats *new);
void	free_ats(t_ats *ats);
int		ats_list_size(t_ats *ats);
void	print_ats(t_ats *ats);
t_ats	*new_ats(t_token *token);

// cd.c
void	cd(char **cmd);

// child.c
pid_t	child(t_token *token, char **envp, t_pipe_fd *fd_pipe, int pipe_i);

// pipe.c
t_pipe_fd *create_pipe(t_ats *ats);
void	close_pipe(t_pipe_fd *fd_pipe);

// parse_tree_list.c
t_parse_tree *new_parse_tree(t_token *token, int token_count, bool is_parse);
void add_back_parse_tree(t_parse_tree **list, t_parse_tree *new);
void			free_parse_tree(t_parse_tree *parse_tree);

// expansion.c
void	expansion(t_token *token);

// variable.c
bool	is_alnum_under(char c);
bool is_al_under(char c);
bool add_variable(char *str);

// variable_list.c
void variable_list_print(void);
void variable_list_add_back(t_variable *new);
t_variable	*variable_list_new(char *key, char *value);
void variable_list_free(void);
char	*get_variable_value(char *key);
char *get_variable_key(char *str);
bool edit_variable(char *key, char *value);

// utils.c
int		is_quote(char c);
int		is_metachar(char c);
int		is_single_quote(char c);
int		is_double_quote(char c);
int strlen_double_ptr(char **str);

// syntax.c
bool	syntax_check(t_token *token);

// env_list.c
void add_back_env(t_env *new);;
char *get_env_key_from_envp(char *env_line);
char *get_env_value_from_envp(char *env_line);
t_env *new_env(char *env_line);
void free_env(void);
void	print_export_env(void);
void	print_env(void);
int	env_list_size(void);
char *get_env_value(char *key);
void export_env(char *key, char *value);
t_env *new_key_value(t_key_value *key_value);

// env.c
void init_env(char **envp);

// builtin_control.c
bool	builtin_check(t_token *token);
bool	builtin_control(t_token *token);

// builtin_cd.c
bool builtin_cd(t_token *token);

// builtin_echo.c
bool builtin_echo(t_token *token);

// builtin_pwd.c
bool builtin_pwd(t_token *token);

// builtin_export.c
bool builtin_export(t_token *token);

// builtin_env.c
bool builtin_env(t_token *token);

// builtin_exit.c
bool	builtin_exit(t_token *token);

#endif
