/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:27:21 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/22 20:07:55 by kosnakam         ###   ########.fr       */
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
	if (!command)
		return ;
	if (command->fdp)
	{
		if (command->fdp->fd)
			free(command->fdp->fd);
		free(command->fdp);
	}
	free(command->pid_info.pid);
	free_ats(command->ats);
	free(command);
}
