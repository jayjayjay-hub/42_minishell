/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:56:56 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/22 18:45:09 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_child_exit(int sig)
{
	(void)sig;
	ft_putendl_fd("", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	sig_child(void)
{
	t_sig	sa;

	sa.sa_handler = &sig_child_exit;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}
