/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:28:58 by kosnakam          #+#    #+#             */
/*   Updated: 2024/04/16 16:44:54 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_a_line(int fd, char *str)
{
	char	*tmp;
	int		index;

	tmp = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	index = 1;
	while (index > 0)
	{
		index = read(fd, tmp, BUFFER_SIZE);
		if (index < 0)
		{
			free(tmp);
			free(str);
			return (NULL);
		}
		tmp[index] = '\0';
		str = gn_ft_strjoin(str, tmp);
		if (gn_ft_strchr(str, '\n'))
			break ;
	}
	free(tmp);
	return (str);
}

char	*get_ret_line(char *str)
{
	char	*ret;
	int		index;

	index = 0;
	if (!str || !*str)
		return (NULL);
	while (str[index] && str[index] != '\n')
		index++;
	ret = gn_ft_calloc(index + 2, sizeof(char));
	if (!ret)
		return (NULL);
	index = 0;
	while (str[index] && str[index] != '\n')
	{
		ret[index] = str[index];
		index++;
	}
	if (str[index] && str[index] == '\n')
		ret[index++] = '\n';
	return (ret);
}

char	*get_next(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	if (!str || !str[i])
	{
		free(str);
		return (NULL);
	}
	ret = gn_ft_calloc((ft_strlen(str) - i + 1), sizeof(char));
	if (!ret)
	{
		free(str);
		return (NULL);
	}
	i++;
	j = 0;
	while (str[i])
		ret[j++] = str[i++];
	free(str);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char		*str[OPEN_MAX];
	char			*ret;

	if (BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	str[fd] = get_a_line(fd, str[fd]);
	ret = get_ret_line(str[fd]);
	str[fd] = get_next(str[fd]);
	return (ret);
}
