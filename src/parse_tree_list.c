/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:27:49 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/17 15:27:51 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse_tree	*new_parse_tree(t_token *token, int token_count, bool is_parse)
{
	t_parse_tree	*new;
	t_token			*tmp;

	new = (t_parse_tree *)malloc(sizeof(t_parse_tree));
	if (!new)
		ft_error(NULL, NULL, "malloc failed", 1);
	tmp = NULL;
	if (is_parse)
	{
		while (token_count > 0)
		{
			token_add_back(&tmp, new_token(token->str, token->type, token->fd));
			token = token->next;
			token_count--;
		}
		new->token = tmp;
	}
	else
		new->token = token;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

void	add_back_parse_tree(t_parse_tree **list, t_parse_tree *new)
{
	t_parse_tree	*tmp;

	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->right)
		tmp = tmp->right;
	tmp->right = new;
}

void	free_parse_tree(t_parse_tree *parse_tree)
{
	t_parse_tree	*tmp;

	while (parse_tree)
	{
		tmp = parse_tree->right;
		free_token(parse_tree->token);
		free(parse_tree);
		parse_tree = tmp;
	}
}
