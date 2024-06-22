/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:31:34 by jtakahas          #+#    #+#             */
/*   Updated: 2024/06/22 14:00:16 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	error_handler(char *main_message, char *sub_message, int status)
{
	write(2, main_message, ft_strlen(main_message));
	if (sub_message)
	{
		write(2, ": ", 2);
		write(2, sub_message, ft_strlen(sub_message));
	}
	write(2, "\n", 1);
	exit(status);
}
