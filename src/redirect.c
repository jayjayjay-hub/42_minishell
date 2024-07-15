
#include "minishell.h"

bool	redirect(t_token **token)
{
	if (!*token)
		return (true);
	if ((*token)->fd < 0)
		return (false);
	if ((*token)->type >= REDIRECT_IN && (*token)->type <= REDIRECT_APPEND)
	{
		if ((*token)->type == REDIRECT_IN || (*token)->type == REDIRECT_HERE_DOC)
		{
			if (((*token)->backup_fd = dup(STDIN_FILENO)) == -1)
				ft_error("minishell", NULL, "dup failed", 1);
			if (dup2((*token)->fd, STDIN_FILENO) == -1)
				ft_error("minishell", NULL, "dup2 failed", 1);
		}
		else
		{
			if (((*token)->backup_fd = dup(STDOUT_FILENO)) == -1)
				ft_error("minishell", NULL, "dup failed", 1);
			if (dup2((*token)->fd, STDOUT_FILENO) == -1)
				ft_error("minishell", NULL, "dup2 failed", 1);
		}
		if (close((*token)->fd) == -1)
			ft_error("minishell", NULL, "cfase failed", 1);
		*token = (*token)->next;
		*token = (*token)->next;
	}
	return (true);
}

void	read_heredoc(char *eof, int tmp_fd)
{
	char *line;

	while (1)
	{
		line = readline("> ");
		if (!line || *line == '\n' || (ft_strlen(line) == ft_strlen(eof) &&
			!ft_strncmp(line, eof, ft_strlen(line))))
		{
			if (!line)
			{
				ft_error("minishell", "warning",
					"here-document delimited by end-of-file", 0);
				break ;
			}
			free(line);
			if (*line == '\n')
				continue ;
			break ;
		}
		ft_putendl_fd(line, tmp_fd);
		free(line);
	}
}

int	open_heredoc(char *eof)
{
	int tmp_fd;
	int fd;

	tmp_fd = open(HEREDOC, O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
	if (tmp_fd == -1)
		ft_error("minishell", "here_doc", "No such file or directory", 0);
	read_heredoc(eof, tmp_fd);
	close(tmp_fd);
	fd = open(HEREDOC, O_RDONLY);
	if (fd == -1)
		ft_error("minishell", "here_doc", "No such file or directory", 0);
	unlink(HEREDOC);
	return (fd);
}

void	redirect_open(t_token *token)
{
	while (token)
	{
		if (token->type == REDIRECT_IN)
			token->fd = open(token->next->str, O_RDONLY);
		else if (token->type == REDIRECT_OUT)
			token->fd = open(token->next->str, O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
		else if (token->type == REDIRECT_APPEND)
			token->fd = open(token->next->str, O_WRONLY | O_CREAT | O_APPEND, S_IREAD | S_IWRITE);
		else if (token->type == REDIRECT_HERE_DOC)
			token->fd = open_heredoc(token->next->str);
		if (token->fd == -1)
			ft_error("minishell", token->next->str, "No such file or directory", 0);
		token = token->next;
	}
}


// backup_fdがないと完成しない
void	close_redirect(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while (token->next)
		token = token->next;
	while (token->prev)
	{
		if (token->type == REDIRECT_IN || token->type == REDIRECT_HERE_DOC)
		{
			if (dup2(token->backup_fd, STDIN_FILENO) == -1)
				ft_error("minishell", "error", "dup2 failed", 1);
			if (close(token->backup_fd) == -1)
				ft_error("minishell", "close", "close failed", 1);
		}
		else if (token->type == REDIRECT_OUT || token->type == REDIRECT_APPEND)
		{
			if (dup2(token->backup_fd, STDOUT_FILENO) == -1)
				ft_error("minishell", "error", "dup2 failed", 1);
			if (close(token->backup_fd) == -1)
				ft_error("minishell", "close", "close failed", 1);
		}
		token = token->prev;
	}
}
