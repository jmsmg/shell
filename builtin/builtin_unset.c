/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 02:32:33 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/15 15:07:20 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_unset_arg_valid(char *arg)
{
	if (arg && *arg)
	{
		if (!ft_isdigit(*arg) && !ft_isalnum(*arg) && !ft_isalpha(*arg))
			return (0);
	}
	return (1);
}

void	do_del_env(t_mini *m, t_envp *envp)
{
	t_envp	*prev;
	t_envp	*next;

	prev = NULL;
	next = NULL;
	if (envp->prev)
		prev = envp->prev;
	if (envp->next)
		next = envp->next;
	if (!(prev) && next)
	{
		m->envp = next;
		next->prev = m->envp;
	}
	else if (prev && next)
	{
		prev->next = next;
		next->prev = prev;
	}
	else if (prev && !next)
		prev->next = NULL;
	free_arr2(envp->dict);
	free(envp->str);
	free(envp);
}

void	delete_env(t_mini *m, char *key)
{
	t_envp	*envp;

	envp = m->envp;
	while (envp)
	{
		if (!ft_strcmp(envp->dict[0], key))
		{
			do_del_env(m, envp);
			break ;
		}
		envp = envp->next;
	}
}

void	builtin_unset(t_mini *m, t_cmd *cmd)
{
	int	idx;

	if (cmd->is_pipe)
		return ;
	else if (get_arr2_len(cmd->args) >= 2)
	{
		idx = 1;
		while (m->cmd->args[idx])
		{
			if (is_env(m, cmd->args[idx]))
				delete_env(m, cmd->args[idx]);
			else if (!is_unset_arg_valid(cmd->args[idx]))
				str_error_handler("unset", cmd->args[idx],
					"not a valid identifier", 1);
			idx++;
		}
	}
}
