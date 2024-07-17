/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:26:16 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/17 15:26:17 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	builtin_pwd(t_token *token)
{
	char	*path;
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
	{
		perror("pwd");
		error_status(256 * 1);
		return (false);
	}
	ft_putendl_fd(buf, 1);
	error_status(0);
	free(buf);
	return (true);
}
