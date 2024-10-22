/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggoc <seonggoc@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 06:38:38 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/17 11:33:13 by seonggoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern long long	g_exit_code;

void	exit_two_arg(t_cmd *cmd, int p_flag)
{
	int	flag;
	int	exit_code;

	flag = 0;
	exit_code = atoi_flag(cmd->args[1], &flag);
	if (!(cmd->prev) && !(cmd->is_pipe))
	{
		if (!p_flag)
			ft_putstr_fd("exit\n", 1);
	}
	if (flag || !exit_code)
	{
		if (!p_flag)
		{
			printf("minishell: exit: %s:\
 numeric argument required\n", cmd->args[1]);
			g_exit_code = 255;
		}
		exit(g_exit_code);
	}
	else
	{
		g_exit_code = exit_code;
		exit(g_exit_code);
	}
}

void	builtin_exit(t_cmd *cmd)
{
	int	p_flag;

	p_flag = 0;
	g_exit_code = 0;
	if (cmd->is_pipe)
		return ;
	if (cmd->prev)
		p_flag = 1;
	if (get_arr2_len(cmd->args) == 1)
	{
		if (!p_flag)
			ft_putstr_fd("exit\n", 1);
		g_exit_code = 0;
		exit(g_exit_code);
	}
	else if (get_arr2_len(cmd->args) == 2)
		exit_two_arg(cmd, p_flag);
	else if (get_arr2_len(cmd->args) >= 3)
	{
		if (!p_flag)
			ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 1);
		g_exit_code = 1;
	}
}
