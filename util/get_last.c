/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 00:16:11 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/15 15:11:50 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*get_last_envp(t_mini *m)
{
	t_envp	*envp;

	envp = m->envp;
	while (envp)
	{
		if (envp->next == NULL)
			return (envp);
		envp = envp->next;
	}
	return (envp);
}

t_cmd	*get_last_cmd(t_cmd *list)
{
	if (!list)
		return (NULL);
	while (list->next)
	{
		list = list->next;
	}
	return (list);
}

t_list	*get_last_list(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
	{
		list = list->next;
	}
	return (list);
}

t_redir	*get_last_redir(t_redir *redir)
{
	if (!redir)
		return (NULL);
	while (redir->next)
	{
		redir = redir->next;
	}
	return (redir);
}
