/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggoc <seonggoc@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:05:06 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/17 12:06:38 by seonggoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_mini *m)
{
	t_cmd	*cmd;
	int		in;
	int		out;

	in = dup(0);
	out = dup(1);
	cmd = m->cmd;
	while (cmd)
	{
		do_fork(m, cmd);
		cmd = cmd->next;
	}
	dup2(in, 0);
	dup2(out, 1);
}
