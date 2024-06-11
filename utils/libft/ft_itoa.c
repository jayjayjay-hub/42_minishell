/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:18:40 by marvin            #+#    #+#             */
/*   Updated: 2023/06/03 12:59:04 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_rtlen(int n, int len)
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

char	*ft_itoa(int n)
{
	char	*str;
	long	nbr;
	size_t	len;

	nbr = n;
	len = 0;
	if (nbr < 0)
		nbr *= -1;
	len = ft_rtlen(n, len);
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
