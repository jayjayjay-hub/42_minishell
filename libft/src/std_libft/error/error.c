/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:31:34 by jtakahas          #+#    #+#             */
/*   Updated: 2024/06/22 11:56:13 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	error_handler(char *main_message, char *sub_message)
{
	ft_printf(RED"Error:"ENDC);
	if (main_message)
		ft_printf(RED" %s"ENDC, main_message);
	if (sub_message)
		ft_printf(" (%s)", sub_message);
	ft_printf("\n");
	exit(1);
}
