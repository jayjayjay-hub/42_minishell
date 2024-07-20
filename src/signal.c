/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jay <jay@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:28:08 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/20 17:30:01 by jay              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	ft_putendl_fd("", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)sig;
}

void	register_signal(void)
{
	struct sigaction	int_sa;
	struct sigaction	quit_sa;

	int_sa.sa_handler = signal_handler;
	sigemptyset(&int_sa.sa_mask);
	sigaddset(&int_sa.sa_mask, SIGINT);
	int_sa.sa_flags = SA_RESTART;

	quit_sa.sa_handler = SIG_IGN;
	sigemptyset(&quit_sa.sa_mask);
	sigaddset(&quit_sa.sa_mask, SIGQUIT);
	quit_sa.sa_flags = 0;

	sigaction(SIGINT, &int_sa, NULL);
	sigaction(SIGQUIT, &quit_sa, NULL);
}


// void	register_signal(void)
// {
// 	t_sig	sa;

// 	sa.sa_handler = signal_handler;
// 	sigemptyset(&sa.sa_mask);
// 	sigaddset(&sa.sa_mask, SIGINT);
// 	sigaddset(&sa.sa_mask, SIGQUIT);
// 	sa.sa_flags = 0;
// 	sigaction(SIGINT, &sa, NULL);
// 	sigaction(SIGQUIT, &sa, NULL);
// }
