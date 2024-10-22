/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_in_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggoc <seonggoc@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:00:33 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/17 11:12:29 by seonggoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_in_out_while(t_cmd *cmd)
{
	cmd->infile_fd = -1;
	cmd->outfile_fd = -1;
	if (!chk_l_redir(cmd))
		return (0);
	if (!chk_r_redir(cmd))
		return (0);
	return (1);
}

void	set_in_out(t_cmd *cmd)
{
	if (!(cmd->l_redir) && !(cmd->r_redir))
	{
		if (cmd->is_pipe && dup2(cmd->fd[1], 1) < 0)
			str_error_handler("Dup2 Error", NULL, NULL, 1);
		if (cmd->prev && cmd->prev->is_pipe && dup2(cmd->prev->fd[0], 0) < 0)
			str_error_handler("Dup2 Error", NULL, NULL, 1);
	}
	else
	{
		if (!set_in_out_while(cmd))
			str_error_handler("Dup2 Error", NULL, NULL, 1);
		if (cmd->outfile_fd == -1 && cmd->is_pipe && dup2(cmd->fd[1], 1) < 0)
			str_error_handler("Dup2 Error", NULL, NULL, 1);
		if (cmd->infile_fd == -1 && cmd->prev && cmd->prev->is_pipe
			&& dup2(cmd->prev->fd[0], 0) < 0)
			str_error_handler("Dup2 Error", NULL, NULL, 1);
	}
}
