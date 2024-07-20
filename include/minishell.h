/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:25:11 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/20 15:03:08 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#  include <sys/wait.h>
#  define S_IREAD S_IRUSR
#  define S_IWRITE S_IWUSR
# endif

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

// exit status
# define CMD_NOT_FOUND	127

# define PRINT_ERROR	-1

// here_doc
# define HEREDOC "/tmp/.heredoc_tmp"

// signal
typedef struct sigaction	t_sig;

typedef struct s_index
{
	int	i;
	int	j;
}	t_index;

typedef struct s_key_value
{
	char	*key;
	char	*value;
}	t_key_value;

typedef struct s_env
{
	char			*key;
	char			*value;
	bool			is_export;
	struct s_env	*next;
}	t_env;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_HERE_DOC,
	REDIRECT_APPEND,
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
	int				fd;
	int				backup_fd;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_variable
{
	char				*key;
	char				*value;
	struct s_variable	*next;
}	t_variable;

typedef struct s_parse_tree
{
	t_token				*token;
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

typedef struct s_cmd
{
	char		**envp;
	t_ats		*ats;
	t_pipe_fd	*fd_pipe;
	t_pid_info	pid_info;
}	t_cmd;

// tokenizer.c
t_token			*tokenize(char *line);
bool			is_valid_variable(char *str);
int				get_word_len(char *line);

// list.c
t_token			*new_token(char *str, t_token_type type, int fd);
void			token_add_back(t_token **list, t_token *new);
void			free_token(t_token *token);
int				token_list_size(t_token *token);

// signal.c
void			register_signal(void);
void			signal_handler(int signum);

// error.c
void			ft_error(char *cmd, char *target,
					char *main_message, int status);
void			handle_eof(char *line);
int				error_status(int error_code);

// redirect.c
bool			redirect(t_token **token);
void			redirect_open(t_token *token);
void			close_redirect(t_token *token);

// parser.c
int				get_pipe_count(t_token *token);
t_ats			*parser(t_token *token);

// ats_list.c
void			add_back_ats(t_ats **list, t_ats *new);
void			free_ats(t_ats *ats);
int				ats_list_size(t_ats *ats);
t_ats			*new_ats(t_token *token);

// child.c
pid_t			child(t_cmd *command, t_env *env);

// pipe.c
t_pipe_fd		*create_pipe(t_ats *ats);
void			close_pipe(t_pipe_fd *fd_pipe);

// parse_tree_list.c
t_parse_tree	*new_parse_tree(t_token *token, int token_count, bool is_parse);
void			add_back_parse_tree(t_parse_tree **list, t_parse_tree *new);
void			free_parse_tree(t_parse_tree *parse_tree);

// expansion.c
void			expansion(t_token *token, t_env *env);

// variable.c
bool			is_alnum_under(char c);
bool			is_al_under(char c);
bool			add_variable(t_token *token, t_env **env);

// variable_list.c
t_variable		*variable_list_new(char *key, char *value);
char			*get_variable_key(char *str);

// utils.c
int				is_quote(char c);
int				is_metachar(char c);
int				is_single_quote(char c);
int				is_double_quote(char c);
int				strlen_double_ptr(char **str);

// syntax.c
bool			syntax_check(t_token *token);

// env_list.c
void			env_add_back(t_env *new, t_env **env);
char			*get_key_from_envp(char *env_line);
char			*get_value_from_envp(char *env_line);
t_env			*new_valiable(char *env_line);
void			free_env(t_env *env);
void			print_export(t_env *env);
void			print_env(t_env *env);
int				env_list_size(t_env *env);
char			*get_env_value(char *key, t_env *env);
bool			edit_env_value(char *key, char *value, t_env **env);
void			export_env(char *key, char *value, t_env **env);
t_env			*new_key_value(t_key_value *key_value);
t_env			*new_export_env(char *env_line);

// env.c
t_env			*init_env(char **envp);

// builtin_control.c
bool			builtin_check(t_token *token);
bool			builtin_control(t_token *token, t_env **env, int child_check);

// builtin_cd.c
bool			builtin_cd(t_token *token, t_env **env);

// builtin_echo.c
bool			builtin_echo(t_token *token);

// builtin_pwd.c
bool			builtin_pwd(void);

// builtin_export.c
bool			builtin_export(t_token *token, t_env **env);

// builtin_env.c
bool			builtin_env(t_env *env);

// builtin_exit.c
bool			builtin_exit(t_token *token);
bool			builtin_exit_child(t_token *token);

// free.c
void			dp_free(char **arg);
void			free_command(t_cmd *command);

// heredoc.c
int				open_heredoc(char *eof);

// childset.c
void			make_wait_child(t_cmd *command, t_env *env);

// expansion_utils.c
void			remove_quote(char *str);

// variable_utils.c
bool			is_valid_token(t_token *token);

// tokenizer_utils.c
char			*get_word(char *line);
char			*get_operator(char *line, t_token_type type);

#endif
