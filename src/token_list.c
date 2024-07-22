/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:28:30 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/20 16:38:53 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_add_back(t_token **list, t_token *new)
{
	t_token	*tmp;

	if (!list || !new)
		return ;
	if (*list == NULL)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

t_token	*new_token(char *str, t_token_type type, int fd)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		ft_error("malloc", "token", strerror(errno), EXIT_FAILURE);
	if (type != WORD)
	{
		token->str = ft_strdup(str);
		if (!token->str)
			ft_error("ft_strdup", "token->str", strerror(errno), EXIT_FAILURE);
	}
	else
	{
		token->str = ft_strdup(str);
		if (!token->str)
			ft_error("ft_strdup", "token->str", strerror(errno), EXIT_FAILURE);
	}
	token->type = type;
	token->fd = fd;
	token->backup_fd = -1;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	delete_top_token(t_token **token)
{
	t_token	*tmp;

	if (!token || !*token)
		return ;
	tmp = (*token)->next;
	free((*token)->str);
	free(*token);
	*token = tmp;
}

int	token_list_size(t_token *token)
{
	long long		size;

	size = 0;
	while (token)
	{
		if (size == INT_MAX)
			return (-1);
		size++;
		token = token->next;
	}
	return (size);
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token->str);
		if (!tmp)
		{
			free(token);
			break ;
		}
		free(token);
		token = tmp;
	}
}
