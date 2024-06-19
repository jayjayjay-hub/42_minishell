/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:38:38 by kosnakam          #+#    #+#             */
/*   Updated: 2024/04/16 12:12:42 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_num_len(unsigned	int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 10;
	}
	return (len);
}

static char	*ft_uitoa(unsigned int n)
{
	char	*num;
	int		len;

	if (n < 0)
		n *= -1;
	len = ft_num_len(n);
	num = (char *)malloc(sizeof(char) * (len + 1));
	if (!num)
		return (NULL);
	num[len--] = '\0';
	while (n != 0)
	{
		num[len--] = n % 10 + 48;
		n = n / 10;
	}
	if (len == 0 && num[1] == '\0')
		num[len] = '0';
	else if (len == 0 && num[1] != '\0')
		num[len] = '-';
	return (num);
}

int	ft_print_unsigned(unsigned int n)
{
	int		count;
	char	*num;

	count = 0;
	if (n == 0)
		count += pt_ft_putchar_fd('0', 1);
	else
	{
		num = ft_uitoa(n);
		count += ft_print_str(num);
		free(num);
	}
	return (count);
}
