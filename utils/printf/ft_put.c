/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:39:25 by kosnakam          #+#    #+#             */
/*   Updated: 2024/04/16 12:25:56 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pt_ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_put_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		pt_ft_putchar_fd(str[i], 1);
		i++;
	}
	return (i);
}
