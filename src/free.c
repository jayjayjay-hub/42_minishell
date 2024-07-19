/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:27:21 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/17 15:27:23 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dp_free(char **arg)
{
	int	i;

	i = -1;
	while (arg[++i])
		free(arg[i]);
	free(arg);
}

void	free_command(t_cmd *command)
{
	free(command->fd_pipe->fd);
	free(command->fd_pipe);
	free(command->pid_info.pid);
	free_ats(command->ats);
	free(command);
}
