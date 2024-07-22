/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:27:27 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/22 16:53:39 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_heredoc(char *eof, int tmp_fd)
{
	char	*line;
	pid_t	pid;
	int	status = 0;

	sig_stop();
	pid = fork();
	if (pid == -1)
		ft_error("minishell", "fork", "fork failed", 0);
	if (pid == 0)
	{
		sig_heredoc();
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
		waitpid(pid, &status, 0);
		register_signal();
	}
	return (status);
}

int	open_heredoc(char *eof)
{
	int	fd;
	int	tmp_fd;
	int	here_doc_check;

	tmp_fd = open(HEREDOC, O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
	if (tmp_fd == -1)
		ft_error("minishell", "here_doc", "No such file or directory", 0);
	here_doc_check = read_heredoc(eof, tmp_fd);
	close(tmp_fd);
	fd = open(HEREDOC, O_RDONLY);
	if (fd == -1)
		ft_error("minishell", "here_doc", "No such file or directory", 0);
	unlink(HEREDOC);
	if (here_doc_check == 2)
	{
		error_status(130 * 256);
		return (130);
	}
	return (fd);
}
