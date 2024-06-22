
#include "minishell.h"

void	redirect_in(t_token **token)
{
	int	fd;

	*token = (*token)->next;
	fd = open((*token)->str, O_RDONLY);
	if (fd == -1)
		ft_error("minishell", (*token)->str, "No such file or directory", 1);
	dup2(fd, STDIN_FILENO);
}

void	redirect_out(t_token **token)
{
	int	fd;

	*token = (*token)->next;
	fd = open((*token)->str, O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
	if (fd == -1)
		ft_error("minishell", (*token)->str, "No such file or directory", 1);
	dup2(fd, STDOUT_FILENO);
}

void	redirect_append(t_token **token)
{
	int	fd;

	*token = (*token)->next;
	fd = open((*token)->str, O_WRONLY | O_CREAT | O_APPEND, S_IREAD | S_IWRITE);
	if (fd == -1)
		ft_error("minishell", (*token)->str, "No such file or directory", 1);
	dup2(fd, STDOUT_FILENO);
}

void	redirect_here_doc(t_token **token)
{
	int		fd;
	char	*line;

	*token = (*token)->next;
	fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
	if (fd == -1)
		ft_error("minishell", "here_doc", "No such file or directory", 1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, (*token)->str, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

void	redirect(t_token **token)
{
	if ((*token)->type == REDIRECT_IN)
		redirect_in(token);
	else if ((*token)->type == REDIRECT_OUT)
		redirect_out(token);
	else if ((*token)->type == REDIRECT_APPEND)
		redirect_append(token);
	else if ((*token)->type == REDIRECT_HERE_DOC)
		redirect_here_doc(token);
}
