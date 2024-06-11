/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:29:11 by kosnakam          #+#    #+#             */
/*   Updated: 2024/04/16 16:46:02 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*gn_ft_strjoin(char *s1, char const *s2)
{
	char	*n_str;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		if (!s1)
			return (NULL);
		*s1 = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	n_str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen((char *) s2) + 1));
	if (!n_str)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		n_str[i] = s1[i];
	while (s2[j])
		n_str[i++] = s2[j++];
	n_str[i] = '\0';
	free(s1);
	return (n_str);
}

int	gn_ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != (char)c)
	{
		if (s[i] == '\0')
			return (0);
		i++;
	}
	return (i);
}

void	gn_ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = '\0';
		i++;
	}
}

void	*gn_ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size > 0 && count >= __SIZE_MAX__ / size)
		return (NULL);
	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (NULL);
	gn_ft_bzero(ptr, count * size);
	return (ptr);
}
