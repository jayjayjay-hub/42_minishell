/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:38:33 by kosnakam          #+#    #+#             */
/*   Updated: 2024/04/16 12:12:31 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hex_len(unsigned	long long num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

void	ft_put_hex(unsigned long long num, const char format)
{
	if (num >= 16)
	{
		ft_put_hex(num / 16, format);
		ft_put_hex(num % 16, format);
	}
	else
	{
		if (num <= 9)
			ft_put_nbr(num);
		else
		{
			if (format == 'X')
				pt_ft_putchar_fd(num + 55, 1);
			else
				pt_ft_putchar_fd(num + 87, 1);
		}
	}
}

int	ft_print_hex(unsigned long long num, const char format)
{
	if (!num)
		return (pt_ft_putchar_fd('0', 1));
	else
		ft_put_hex(num, format);
	return (ft_hex_len(num));
}
