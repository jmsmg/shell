/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:10:25 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/15 18:37:31 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern long long	g_exit_code;

void	cd_relative(t_mini *m, t_cmd *cmd, char *now)
{
	char	*path;
	int		res;

	path = ft_slushjoin(now, cmd->args[1]);
	res = chdir(path);
	if (res == -1)
		str_error_handler("cd", cmd->args[1], "No such file or directory", 1);
	else
		make_oldpwd(m, now);
	free(path);
}

void	cd_absolute(t_mini *m, t_cmd *cmd, char *now)
{
	int		res;

	res = chdir(cmd->args[1]);
	if (res == -1)
		str_error_handler("cd", cmd->args[1], "No such file or directory", 1);
	else
		make_oldpwd(m, now);
}

void	cd_home(t_mini *m, char *now)
{
	char	*home;
	int		res;

	home = get_env_home(m);
	if (!home)
		str_error_handler("cd", NULL, "HOME not set", 1);
	else
	{
		res = chdir(home);
		if (res == -1)
			str_error_handler("cd", home, "No such file or directory", 1);
		else
			make_oldpwd(m, now);
	}
	free(home);
}

void	builtin_cd(t_mini *m, t_cmd *cmd)
{
	char	*now;

	now = getcwd(NULL, 0);
	if (!now)
	{
		str_error_handler("getcwd", NULL, "does not work", 1);
		exit(g_exit_code);
	}
	if (cmd->args[1] == NULL)
		cd_home(m, now);
	else if (!ft_strncmp(cmd->args[1], "/", 1))
		cd_absolute(m, cmd, now);
	else
		cd_relative(m, cmd, now);
	if (now)
		free(now);
}
