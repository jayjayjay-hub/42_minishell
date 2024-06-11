/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:21:17 by kosnakam          #+#    #+#             */
/*   Updated: 2024/04/16 12:13:12 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_conversion(va_list *ap, const char format)
{
	int	count;

	count = 0;
	if (format == 'c')
		count += pt_ft_putchar_fd(va_arg(*ap, int), 1);
	else if (format == 's')
		count += ft_print_str(va_arg(*ap, char *));
	else if (format == 'p')
		count += ft_print_ptr(va_arg(*ap, unsigned long long));
	else if (format == 'd' || format == 'i')
		count += ft_put_nbr(va_arg(*ap, int));
	else if (format == 'u')
		count += ft_print_unsigned(va_arg(*ap, unsigned int));
	else if (format == 'x' || format == 'X')
		count += ft_print_hex(va_arg(*ap, unsigned int), format);
	else if (format == '%')
		count += pt_ft_putchar_fd('%', 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	ap;

	i = 0;
	count = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
			count += ft_conversion(&ap, format[++i]);
		else
			count += pt_ft_putchar_fd(format[i], 1);
		i++;
	}
	va_end(ap);
	return (count);
}
