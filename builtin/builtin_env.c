/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:10:08 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/08 15:37:46 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_envp *envp)
{
	while (envp)
	{
		ft_putstr_fd(envp->str, 1);
		ft_putstr_fd("\n", 1);
		envp = envp->next;
	}
}

void	builtin_env(t_mini *m, t_cmd *cmd)
{
	t_envp	*envp;

	envp = m->envp;
	if (!(cmd->args[1]))
		print_env(envp);
	else if (cmd->args[1])
	{
		while (envp)
		{
			if (!ft_strcmp(envp->dict[0], cmd->args[1]))
			{
				ft_putstr_fd(envp->dict[1], 1);
				ft_putstr_fd("\n", 1);
				break ;
			}
			envp = envp->next;
		}
	}
	if (!envp)
		str_error_handler(cmd->args[0],
			cmd->args[1], "No such file or directory", 1);
}
