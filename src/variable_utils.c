/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:45:20 by jtakahas          #+#    #+#             */
/*   Updated: 2024/07/17 15:46:12 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_token(t_token *token)
{
	while (token)
	{
		if (!is_valid_variable(token->str))
			return (false);
		token = token->next;
	}
	return (true);
}
