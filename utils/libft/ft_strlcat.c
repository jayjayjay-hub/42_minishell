/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:47:13 by kosnakam          #+#    #+#             */
/*   Updated: 2023/05/27 19:20:21 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_size;
	size_t	dest_size;
	size_t	i;

	src_size = 0;
	dest_size = 0;
	while (src[src_size])
		src_size++;
	if (size == 0)
		return (src_size);
	while (dst[dest_size])
		dest_size++;
	if (size <= dest_size)
		return (size + src_size);
	i = 0;
	size--;
	while (size && (size - dest_size) && src[i])
	{
		dst[dest_size + i] = src[i];
		i++;
		size--;
	}
	dst[dest_size + i] = '\0';
	return (src_size + dest_size);
}
