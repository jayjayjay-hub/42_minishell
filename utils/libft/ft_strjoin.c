/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:16:46 by kosnakam          #+#    #+#             */
/*   Updated: 2023/06/01 17:35:32 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*n_str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	n_str = (char *)malloc(sizeof(char) * (ft_strlen((char *) s1)
				+ ft_strlen((char *) s2)) + 1);
	if (!n_str)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
		n_str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		n_str[j++] = s2[i++];
	n_str[j] = '\0';
	return (n_str);
}
