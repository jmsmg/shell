/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggoc <seonggoc@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:37:40 by seungmin          #+#    #+#             */
/*   Updated: 2023/11/17 11:21:06 by seonggoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern long long	g_exit_code;

void	close_fd(t_cmd *cmd)
{
	if (cmd->is_pipe)
	{
		close(cmd->fd[1]);
		if (!cmd->next)
			close(cmd->fd[0]);
	}
	if (cmd->prev && cmd->prev->outfile_fd != -1)
		close(cmd->prev->outfile_fd);
	if (cmd->prev && cmd->prev->is_pipe)
		close(cmd->prev->fd[0]);
}

void	fork_child(t_mini *m, t_cmd *cmd)
{
	char	**envp;

	envp = make_envp(m);
	set_in_out(cmd);
	if (cmd->outfile_fd != -1)
	{
		close(cmd->outfile_fd);
	}
	if (is_builtin(cmd->args[0]))
		builtin_center(m, cmd);
	else if (chk_file_exist(cmd, chk_path(m))
		&& cmd->cmd_file
		&& execve(cmd->cmd_file, cmd->args, envp) < 0)
	{
		ft_putstr_fd("error: cannot execute ", 1);
		ft_putstr_fd(cmd->args[0], 1);
		ft_putstr_fd("\n", 1);
	}
	exit(g_exit_code);
}

void	do_fork(t_mini *m, t_cmd *cmd)
{
	pid_t	pid;

	if (cmd->is_pipe)
		if (pipe(cmd->fd) < 0)
			exit(1);
	process_signal(DFL, DFL);
	pid = fork();
	if (pid < 0)
		exit(1);
	else if (pid == 0)
		fork_child(m, cmd);
	else
	{
		close_fd(cmd);
		if (cmd->is_dlft)
			wait_child(0, 0);
		process_signal(IGN, IGN);
	}
}
