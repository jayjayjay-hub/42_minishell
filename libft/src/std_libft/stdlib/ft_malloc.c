/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 12:00:19 by jtakahas          #+#    #+#             */
/*   Updated: 2024/06/22 12:05:05 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(size_t size, t_malloc_list **malloc_list)
{
	void			*ptr;
	t_malloc_list	*new;

	ptr = malloc(size);
	if (!ptr)
		error_handler(strerror(errno), NULL);
	new = malloc(sizeof(t_malloc_list));
	if (!new)
		error_handler(strerror(errno), NULL);
	new->ptr = ptr;
	new->next = *malloc_list;
	*malloc_list = new;
	return (ptr);
}

void	free_malloc_list(t_malloc_list *malloc_list)
{
	t_malloc_list	*tmp;

	while (malloc_list)
	{
		tmp = malloc_list;
		malloc_list = malloc_list->next;
		free(tmp->ptr);
		free(tmp);
	}
}
