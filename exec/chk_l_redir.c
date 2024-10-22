/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_l_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggoc <seonggoc@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:36:58 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/17 10:39:51 by seonggoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	chk_left_redir(t_redir *r, t_cmd *cmd)
{
	int	fd;

	fd = open(r->str, O_RDONLY, 0644);
	if (fd == -1)
	{
		str_error_handler(r->str, NULL, "No such file or directory", 1);
		return (0);
	}
	else
		cmd->infile_fd = fd;
	return (1);
}

void	dlft_while(t_redir *r, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, r->str))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int	chk_dlft_redir(t_redir *r, t_cmd *cmd)
{
	int			fd;
	char		*tmp;

	tmp = "/tmp/tmp.tmp";
	fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		str_error_handler(r->str, NULL, "fd does not open", 1);
		return (0);
	}
	else
	{
		dlft_while(r, fd);
		close(fd);
		fd = open(tmp, O_RDONLY, 0644);
		if (fd == -1)
		{
			str_error_handler(r->str, NULL, "fd does not open", 1);
			return (0);
		}
		cmd->infile_fd = fd;
	}
	return (1);
}

int	chk_l_redir(t_cmd *cmd)
{
	t_redir	*r;

	r = cmd->l_redir;
	while (r)
	{
		if (r->type == LEFT && r->str && !chk_left_redir(r, cmd))
			return (0);
		if (r->type == DLFT && r->str && !chk_dlft_redir(r, cmd))
			return (0);
		if (r->next)
			close(cmd->infile_fd);
		else
		{
			if (dup2(cmd->infile_fd, 0) < 0)
				str_error_handler("Dup2 Error", NULL, NULL, 1);
			close(cmd->infile_fd);
		}
		r = r->next;
	}
	return (1);
}
