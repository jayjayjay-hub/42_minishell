/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:48:25 by kosnakam          #+#    #+#             */
/*   Updated: 2023/05/30 17:50:21 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	s_len;

	if (!s)
		return (NULL);
	if (!*s)
		return (ft_strdup(s));
	s_len = ft_strlen((char *)s);
	if (s_len > len)
		new_str = (char *)malloc(len + 1);
	else
		new_str = (char *)malloc(s_len + 1);
	if (!new_str)
		return (NULL);
	i = start;
	j = 0;
	while (i < s_len && j < len)
		new_str[j++] = s[i++];
	new_str[j] = '\0';
	return (new_str);
}
