
#include "minishell.h"

// void	redirect_in(t_token **token)
// {
// 	int	fd;

// 	*token = (*token)->next;
// 	fd = open((*token)->str, O_RDONLY);
// 	if (fd == -1)
// 		ft_error("minishell", (*token)->str, "No such file or directory", 1);
// 	dup2(fd, STDIN_FILENO);
// 	close(fd);
// 	*token = (*token)->next;
// }

// void	redirect_out(t_token **token)
// {
// 	int	fd;

// 	*token = (*token)->next;
// 	// overwirte check start
// 	// fd = open((*token)->str, O_RDONLY);
// 	// if (fd != -1)
// 	// 	ft_error("minishell", (*token)->str, "cannot overwrite existing file", 1);
// 	// overwirte check end
// 	fd = open((*token)->str, O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
// 	if (fd == -1)
// 		ft_error("minishell", (*token)->str, "No such file or directory", 1);
// 	dup2(fd, STDOUT_FILENO);
// 	close(fd);
// 	*token = (*token)->next;
// }

// void	redirect_append(t_token **token)
// {
// 	int	fd;

// 	*token = (*token)->next;
// 	fd = open((*token)->str, O_WRONLY | O_CREAT | O_APPEND, S_IREAD | S_IWRITE);
// 	if (fd == -1)
// 		ft_error("minishell", (*token)->str, "No such file or directory", 1);
// 	dup2(fd, STDOUT_FILENO);
// 	close(fd);
// 	*token = (*token)->next;
// }

// void	redirect_here_doc(t_token **token)
// {
// 	int		tmp_fd;
// 	int		fd;
// 	char	*line;

// 	*token = (*token)->next;
// 	tmp_fd = open(HEREDOC, O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
// 	if (tmp_fd == -1)
// 		ft_error("minishell", "here_doc", "No such file or directory", 1);
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line || *line == '\n' || (ft_strlen(line) == ft_strlen((*token)->str) && !ft_strncmp(line, (*token)->str, ft_strlen(line))))
// 		{
// 			free(line);
// 			if (*line == '\n')
// 				continue ;
// 			break ;
// 		}
// 		ft_putendl_fd(line, tmp_fd);
// 		free(line);
// 	}
// 	fd = open(HEREDOC, O_RDONLY);
// 	dup2(fd, STDIN_FILENO);
// 	close(fd);
// 	unlink(HEREDOC);
// 	*token = (*token)->next;
// }

// void	redirect(t_token **token)
// {
// 	if (!*token)
// 		return ;
// 	syntax_check(*token);
// 	if ((*token)->type == REDIRECT_IN)
// 		redirect_in(token);
// 	else if ((*token)->type == REDIRECT_OUT)
// 		redirect_out(token);
// 	else if ((*token)->type == REDIRECT_APPEND)
// 		redirect_append(token);
// 	else if ((*token)->type == REDIRECT_HERE_DOC)
// 		redirect_here_doc(token);
// }

void	redirect(t_token **token)
{
	if (!*token)
		return ;
	if ((*token)->type >= REDIRECT_IN && (*token)->type <= REDIRECT_APPEND)
	{
		printf("token.fd = %d\n", (*token)->fd);
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

int	open_heredoc(char *eof)
{
	int tmp_fd;
	int fd;
	char *line;


	tmp_fd = open(HEREDOC, O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
	if (tmp_fd == -1)
		ft_error("minishell", "here_doc", "No such file or directory", 1);
	while (1)
	{
		line = readline("> ");
		if (!line || *line == '\n' || (ft_strlen(line) == ft_strlen(eof) && !ft_strncmp(line, eof, ft_strlen(line))))
		{
			free(line);
			if (*line == '\n')
				continue ;
			break ;
		}
		ft_putendl_fd(line, tmp_fd);
		free(line);
	}
	close(tmp_fd);
	fd = open(HEREDOC, O_RDONLY);
	unlink(HEREDOC);
	return (fd);
}

int	redirect_open(t_token *token)
{
	int fd;

	fd = 0;
	if (!token->next || token->next->type != WORD)
		return (0);
	if (token->type == REDIRECT_IN)
		fd = open(token->next->str, O_RDONLY);
	else if (token->type == REDIRECT_OUT)
		fd = open(token->next->str, O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
	else if (token->type == REDIRECT_APPEND)
		fd = open(token->next->str, O_WRONLY | O_CREAT | O_APPEND, S_IREAD | S_IWRITE);
	else if (token->type == REDIRECT_HERE_DOC)
		fd = open_heredoc(token->next->str);
	if (fd == -1)
		ft_error("minishell", token->next->str, "No such file or directory", 1);
	return (fd);
}
