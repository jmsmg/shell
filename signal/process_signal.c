/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggoc <seonggoc@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:18:36 by seonggoc          #+#    #+#             */
/*   Updated: 2023/11/17 09:51:59 by seonggoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	process_signal(int cntl_c, int cntl_back)
{
	if (cntl_c == IGN)
		signal(SIGINT, SIG_IGN);
	if (cntl_c == DFL)
		signal(SIGINT, SIG_DFL);
	if (cntl_c == USR)
		signal(SIGINT, signal_handler);
	if (cntl_back == IGN)
		signal(SIGQUIT, SIG_IGN);
	if (cntl_back == DFL)
		signal(SIGQUIT, SIG_DFL);
	if (cntl_back == USR)
		signal(SIGQUIT, signal_handler);
}
