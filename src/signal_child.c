/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:56:56 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/22 20:01:58 by kosnakam         ###   ########.fr       */
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

void	sig_child_quit(int sig)
{
	(void)sig;
	ft_putendl_fd("Quit (core dumped)", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	sig_child(void)
{
	t_sig	int_sa;
	t_sig	quit_sa;

	int_sa.sa_handler = &sig_child_exit;
	sigemptyset(&int_sa.sa_mask);
	sigaddset(&int_sa.sa_mask, SIGINT);
	int_sa.sa_flags = SA_RESTART;
	quit_sa.sa_handler = &sig_child_quit;
	sigemptyset(&quit_sa.sa_mask);
	sigaddset(&quit_sa.sa_mask, SIGQUIT);
	quit_sa.sa_flags = 0;
	sigaction(SIGINT, &int_sa, NULL);
	sigaction(SIGQUIT, &quit_sa, NULL);
}
