/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:31:17 by marvin            #+#    #+#             */
/*   Updated: 2023/06/03 19:25:12 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	all_free(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static int	ft_count_words(char const *s, char c)
{
	int	i;
	int	flag;
	int	counter;

	i = 0;
	flag = 0;
	counter = 0;
	while (s[i])
	{
		if (s[i] != c && flag == 0)
		{
			flag = 1;
			counter++;
		}
		else if (s[i] == c)
			flag = 0;
		i++;
	}
	return (counter);
}

static char	**part_of_split(char const *s, char c, char **split, size_t i)
{
	size_t	j;
	int		index;

	j = 0;
	index = -1;
	while (i <= ft_strlen((char *)s))
	{
		if (s[i] != c && index == -1)
			index = i;
		else if ((s[i] == c || i == ft_strlen((char *) s)) && index >= 0)
		{
			split[j] = ft_substr(s, index, i - index);
			if (!split[j])
			{
				all_free(split);
				return (NULL);
			}
			index = -1;
			j++;
		}
		i++;
	}
	split[j] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	split = (char **)malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	split = part_of_split(s, c, split, i);
	return (split);
}
