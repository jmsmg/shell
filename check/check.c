/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:47:55 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/15 21:11:20 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern long long	g_exit_code;

int	get_file_path(t_cmd *cmd, char **file_dir)
{
	int		i;
	char	*p;

	i = 0;
	while (file_dir && file_dir[i])
	{
		p = ft_slushjoin(file_dir[i], cmd->args[0]);
		if (access(p, X_OK) == 0)
		{
			cmd->cmd_file = p;
			return (1);
		}
		free(p);
		i++;
	}
	return (0);
}

int	chk_file_dir(t_cmd *cmd)
{
	struct stat	s;
	int			len;

	if (!(cmd->args[0]) || !(cmd))
		return (0);
	len = ft_strlen(cmd->args[0]);
	if (((len >= 1 && !ft_strncmp(cmd->args[0], "/", 1))
			|| (len >= 2 && !ft_strncmp(cmd->args[0], "./", 2)))
		&& stat(cmd->args[0], &s) != -1 && S_ISDIR(s.st_mode))
	{
		str_error_handler(cmd->args[0], NULL, "is a directory", 126);
		return (1);
	}
	return (0);
}

int	chk_file_exist(t_cmd *cmd, char **file_dir)
{
	if (!(cmd->args[0]) || !(cmd))
		return (0);
	if (access(cmd->args[0], X_OK) == 0)
	{
		cmd->cmd_file = ft_strdup(cmd->args[0]);
		return (1);
	}
	if (get_file_path(cmd, file_dir))
		return (1);
	if (ft_strnstr(cmd->args[0], "/", ft_strlen(cmd->args[0])))
		str_error_handler(cmd->args[0], NULL, "No such file or directory", 127);
	else
		str_error_handler(cmd->args[0], NULL, "command not found", 127);
	return (0);
}

char	**chk_path(t_mini *m)
{
	char	**tmp;
	t_envp	*envp;

	envp = m->envp;
	while (envp)
	{
		if (ft_strnstr(envp->dict[0], "PATH", 4))
		{
			tmp = ft_split(envp->dict[1], ':');
			return (tmp);
		}
		envp = envp->next;
	}
	return (NULL);
}

char	*str_join(char *a, char *b)
{
	char	*result;

	result = ft_strjoin(a, b);
	free(a);
	return (result);
}
