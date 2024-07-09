
#include "minishell.h"

void	redirect(t_token **token)
{
	if (!*token)
		return ;
	if ((*token)->type >= REDIRECT_IN && (*token)->type <= REDIRECT_APPEND)
	{
		if ((*token)->type == REDIRECT_IN)
			dup2((*token)->fd, STDIN_FILENO);
		else if ((*token)->type == REDIRECT_OUT)
			dup2((*token)->fd, STDOUT_FILENO);
		else if ((*token)->type == REDIRECT_APPEND)
			dup2((*token)->fd, STDOUT_FILENO);
		else if ((*token)->type == REDIRECT_HERE_DOC)
			dup2((*token)->fd, STDIN_FILENO);
		close((*token)->fd);
		*token = (*token)->next;
		*token = (*token)->next;
	}
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
					"here-document was delimited by end-of-file", 0);
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
		ft_error("minishell", "here_doc", "No such file or directory", 1);
	read_heredoc(eof, tmp_fd);
	close(tmp_fd);
	fd = open(HEREDOC, O_RDONLY);
	if (fd == -1)
		ft_error("minishell", "here_doc", "No such file or directory", 1);
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
			ft_error("minishell", token->next->str, "No such file or directory", 1);
		token = token->next;
	}
}

void	close_redirect(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type >= REDIRECT_IN && tmp->type <= REDIRECT_APPEND)
			close(tmp->fd);
		tmp = tmp->next;
	}
}
