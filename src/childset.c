/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:50:27 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/22 17:06:34 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_loop(t_cmd *command, t_env *env)
{
	while (command->ats)
	{
		command->pid_info.pid[command->pid_info.pipe_i] = child(command, env);
		command->pid_info.pipe_i++;
		command->ats = command->ats->next;
	}
}

void	wait_child(t_pid_info pid_info)
{
	int		i;
	int		status;

	i = 0;
	status = 0;
	while (pid_info.pipe_i--)
	{
		waitpid(pid_info.pid[i++], &status, 0);
		error_status(status);
		register_signal();
	}
}

void	make_wait_child(t_cmd *command, t_env *env)
{
	t_ats	*tmp;

	tmp = command->ats;
	command->fd_pipe = create_pipe(command->ats);
	command->pid_info.pid = (pid_t *)malloc(sizeof(pid_t)
			* (command->fd_pipe->pipe_size + 1));
	if (!command->fd_pipe->pipe_size
		&& builtin_control(command->ats->token,
			&env, 0, command->fd_pipe->pipe_size))
	{
		close_redirect(command->ats->token);
		error_status(PRINT_ERROR);
		return ;
	}
	execve_loop(command, env);
	close_pipe(command->fd_pipe);
	wait_child(command->pid_info);
	if (!command->fd_pipe->pipe_size && builtin_check(tmp->token, 0))
		close_redirect(tmp->token);
	free_ats(tmp);
}
