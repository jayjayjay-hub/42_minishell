/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jay <jay@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:27:27 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/20 17:27:20 by jay              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler_exit(int sig)
{
	(void)sig;
	signal(SIGINT, SIG_DFL);
	ft_putendl_fd("", 1);
	rl_on_new_line();
	kill(0, SIGINT);
}

void	sig_heredoc_mode(void)
{
	t_sig	sa;

	sa.sa_handler = &sigint_handler_exit;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}

void	sig_stop(void)
{
	struct sigaction	stop_sa;

	stop_sa.sa_handler = SIG_IGN;
	stop_sa.sa_flags = 0;
	sigaction(SIGINT, &stop_sa, NULL);
}

void	read_heredoc(char *eof, int tmp_fd)
{
	char	*line;
	pid_t	pid;

	sig_stop();
	pid = fork();
	if (pid == -1)
		ft_error("minishell", "fork", "fork failed", 0);
	if (pid == 0)
	{
		sig_heredoc_mode();
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
					exit(0);
				}
				if (line[0] == '\n')
				{
					free(line);
					continue ;
				}
				free(line);
				exit(0);
			}
			ft_putendl_fd(line, tmp_fd);
			free(line);
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
		register_signal();
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
