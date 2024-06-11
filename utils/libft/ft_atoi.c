/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:25:58 by kosnakam          #+#    #+#             */
/*   Updated: 2023/06/10 11:38:03 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_max_result(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (ft_isdigit(str[i]))
	{
		if (result > LONG_MAX / 10)
			return (LONG_MAX);
		if (result * 10 > LONG_MAX - str[i] + '0')
			return (LONG_MAX);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

static long	ft_min_result(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (ft_isdigit(str[i]))
	{
		if (result < LONG_MIN / 10)
			return (LONG_MIN);
		if (result * 10 < LONG_MIN + str[i] - '0')
			return (LONG_MIN);
		result = result * 10 - (str[i] - '0');
		i++;
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	sum;
	int		minus;

	i = 0;
	sum = 0;
	minus = 1;
	if (!str && !*str)
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		minus = -1;
	if (str[i] == '+' || minus == -1)
		i++;
	if (minus == 1)
		return ((int)ft_max_result(&str[i]));
	else
		return ((int)ft_min_result(&str[i]));
}
