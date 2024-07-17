
#include "minishell.h"

void	read_heredoc(char *eof, int tmp_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || *line == '\n' || (ft_strlen(line) == ft_strlen(eof)
				&& !ft_strncmp(line, eof, ft_strlen(line))))
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
	int	fd;
	int	tmp_fd;

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
