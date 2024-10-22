/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggoc <seonggoc@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:11:28 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/17 09:50:40 by seonggoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	g_exit_code;

void	set_input_termios(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	process_signal(USR, USR);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini				m;
	struct termios		term;

	tcgetattr(STDIN_FILENO, &term);
	check_validation(argc, argv);
	init(&m, envp);
	set_input_termios();
	do_readline(&m);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
