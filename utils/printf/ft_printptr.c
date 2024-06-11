/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:53:13 by kosnakam          #+#    #+#             */
/*   Updated: 2024/04/16 12:13:20 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_ptr(unsigned long long ptr)
{
	int	count;

	count = 0;
	count += ft_put_str("0x");
	if (!ptr)
		count += pt_ft_putchar_fd('0', 1);
	else
	{
		ft_put_hex(ptr, 'p');
		count += ft_hex_len(ptr);
	}
	return (count);
}
