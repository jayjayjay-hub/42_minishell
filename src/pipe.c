
#include "minishell.h"

int *create_pipe(t_ats *ats)
{
	int		*fd;
	t_ats	*tmp_ats;
	int		i = 0;

	tmp_ats = ats;
	fd = malloc(sizeof(int) * 100); // 100は(atsの数-1)*2
	if (!fd)
		ft_error("minishell", NULL, "malloc failed", 1);
	while (tmp_ats->next)
	{
		if (pipe(fd + 2 * i) == -1)
			ft_error("minishell", NULL, "pipe failed", 1);
		tmp_ats = tmp_ats->next;
		i++;
	}
	if (i == 0)
	{
		free(fd);
		return (NULL);
	}
	return (fd);
}
