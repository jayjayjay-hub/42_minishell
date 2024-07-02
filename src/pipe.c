
#include "minishell.h"

t_pipe_fd *create_pipe(t_ats *ats)
{
	t_pipe_fd	*fd;
	t_ats	*tmp_ats;
	int		i = 0;

	tmp_ats = ats;
	fd = (t_pipe_fd *)malloc(sizeof(t_pipe_fd));
	if (!fd)
		ft_error("minishell", NULL, "malloc failed", 1);
	fd->fd = (int *)malloc(sizeof(int) * get_pipe_count(ats->token));
	if (!fd->fd)
		ft_error("minishell", NULL, "malloc failed", 1);
	while (tmp_ats && tmp_ats->next)
	{
		if (pipe(fd->fd + 2 * i) == -1)
			ft_error("minishell", NULL, "pipe failed", 1);
		tmp_ats = tmp_ats->next;
		i++;
	}
	fd->pipe_size = i;
	return (fd);
}

void	close_pipe(t_pipe_fd *fd_pipe)
{
	int		i;

	i = 0;
	if (!fd_pipe || fd_pipe->pipe_size == 0)
		return ;
	fd_pipe->pipe_size *= 2;
	while (i <= fd_pipe->pipe_size)
	{
		if (fd_pipe->fd[i] != 0 && fd_pipe->fd[i] != 1)
			close(fd_pipe->fd[i]);
		i++;
	}
}
