/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 19:09:16 by kosnakam          #+#    #+#             */
/*   Updated: 2024/04/16 12:13:36 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_put_str("(null)");
		return (6);
	}
	while (str[i])
		pt_ft_putchar_fd(str[i++], 1);
	return (i);
}

static int	ft_num_len(int n, int len)
{
	if (n > 0)
		len = 0;
	else
		len = 1;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static char	*ft_itoa(int n)
{
	char	*str;
	long	nbr;
	size_t	len;

	nbr = n;
	len = 0;
	if (nbr < 0)
		nbr *= -1;
	len = ft_num_len(n, len);
	str = (char *) malloc(len + 1);
	if (!str)
		return (0);
	str[len--] = '\0';
	while (nbr > 0)
	{
		str[len--] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (len == 0 && str[1] == '\0')
		str[len] = '0';
	else if (len == 0 && str[1] != '\0')
		str[len] = '-';
	return (str);
}

int	ft_put_nbr(int n)
{
	int		len;
	char	*num;

	len = 0;
	num = ft_itoa(n);
	len = ft_print_str(num);
	free(num);
	return (len);
}
