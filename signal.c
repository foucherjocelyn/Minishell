/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:53:13 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/14 17:49:11 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_non_interactiv_signals(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		write(1, "\n", 1);
	}
	if (signum == SIGQUIT)
	{	
		write(1, "Quit (core dumped)\n", 19);
	}
}

void	handle_interactiv_signals(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 130;
	}
}
