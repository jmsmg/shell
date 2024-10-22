/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_nopipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggoc <seonggoc@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:05:06 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/17 12:06:34 by seonggoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern long long	g_exit_code;

void	fork_child_nopipe(t_mini *m, t_cmd *cmd)
{
	char	**envp;

	envp = make_envp(m);
	set_in_out(cmd);
	if (!chk_file_dir(cmd) && chk_file_exist(cmd, chk_path(m))
		&& cmd->cmd_file
		&& execve(cmd->cmd_file, cmd->args, envp) < 0)
	{
		str_error_handler(cmd->args[0], NULL, "error: cannot execute", 1);
	}
	exit(g_exit_code);
}

void	do_fork_nopipe(t_mini *m, t_cmd *cmd)
{
	pid_t	pid;

	if (cmd->is_pipe)
		if (pipe(cmd->fd) < 0)
			str_error_handler("Pipe Error", NULL, NULL, 1);
	process_signal(DFL, DFL);
	pid = fork();
	if (pid < 0)
		str_error_handler("Fork Error", NULL, NULL, 1);
	else if (pid == 0)
		fork_child_nopipe(m, cmd);
	else
	{
		if (cmd->outfile_fd != -1)
			close(cmd->outfile_fd);
		process_signal(IGN, IGN);
	}
}

void	exec_nopipe(t_mini *m)
{
	int	in;
	int	out;

	in = dup(0);
	out = dup(1);
	if (m->cmd->args[0] && is_builtin(m->cmd->args[0]))
	{
		set_in_out_while(m->cmd);
		builtin_center(m, m->cmd);
		if (m->cmd->outfile_fd != -1)
			close(m->cmd->outfile_fd);
	}
	else
		do_fork_nopipe(m, m->cmd);
	dup2(in, 0);
	dup2(out, 1);
}
