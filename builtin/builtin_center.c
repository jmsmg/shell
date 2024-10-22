/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_center.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggoc <seonggoc@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:10:10 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/17 11:31:46 by seonggoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_center(t_mini *m, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "pwd"))
		builtin_pwd();
	else if (!ft_strcmp(cmd->args[0], "env"))
		builtin_env(m, cmd);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		builtin_cd(m, cmd);
	else if (!ft_strcmp(cmd->args[0], "echo"))
		builtin_echo(cmd);
	else if (!ft_strcmp(cmd->args[0], "export"))
		builtin_export(m, cmd);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		builtin_unset(m, cmd);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		builtin_exit(cmd);
}

int	is_builtin(char *str)
{
	int	ret;

	ret = 0;
	if (!str)
		return (0);
	if (!ft_strcmp(str, "pwd") || !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "cd") || !ft_strcmp(str, "echo")
		|| !ft_strcmp(str, "export") || !ft_strcmp(str, "unset")
		|| !ft_strcmp(str, "exit"))
		return (1);
	else
		return (0);
	return (ret);
}
