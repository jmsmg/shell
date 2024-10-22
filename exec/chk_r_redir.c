/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_r_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggoc <seonggoc@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:47:13 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/17 10:35:06 by seonggoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	chk_right_redir(t_redir *r, t_cmd *cmd)
{
	int	fd;

	fd = open(r->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		str_error_handler(r->str, NULL, "No such file or directory", 1);
		return (0);
	}
	else
	{
		if (dup2(fd, 1) < 0)
			str_error_handler("Dup2 Error", NULL, NULL, 1);
		if (cmd->prev && cmd->prev->outfile_fd != -1)
			close(cmd->prev->outfile_fd);
		cmd->outfile_fd = fd;
	}
	return (1);
}

int	chk_drgt_redir(t_redir *r, t_cmd *cmd)
{
	int	fd;

	fd = open(r->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		str_error_handler(r->str, NULL, "fd does not open", 1);
		return (0);
	}
	else
	{
		if (dup2(fd, 1) < 0)
			str_error_handler("Dup2 Error", NULL, NULL, 1);
		if (cmd->prev && cmd->prev->outfile_fd != -1)
			close(cmd->prev->outfile_fd);
		cmd->outfile_fd = fd;
	}
	return (1);
}

int	chk_r_redir(t_cmd *cmd)
{
	t_redir	*r;

	r = cmd->r_redir;
	while (r)
	{
		if (r->type == RIGT && r->str && !chk_right_redir(r, cmd))
			return (0);
		if (r->type == DRGT && r->str && !chk_drgt_redir(r, cmd))
			return (0);
		r = r->next;
	}
	return (1);
}
