/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggoc <seonggoc@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:11:45 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/15 18:17:30 by seonggoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_mini *m)
{
	t_envp	*envp;

	envp = m->envp;
	while (envp)
	{
		if (envp->str)
			free(envp->str);
		if (envp->dict)
		{
			free(envp->dict[0]);
			free(envp->dict[1]);
			free(envp->dict);
		}
		envp = envp->next;
	}
	if (m->envp)
		free(m->envp);
}

void	free_list(t_mini *m)
{
	t_list	*l;
	t_list	*prev;

	if (m->list)
		l = m->list;
	else
		l = NULL;
	while (l)
	{
		if (l->str)
			free(l->str);
		prev = l;
		l = l->next;
		free(prev);
	}
	m->list = lstnew();
}

void	free_redir(t_redir *redir)
{
	t_redir	*r;
	t_redir	*tmp;

	r = redir;
	while (r)
	{
		if (r->str)
			free(r->str);
		tmp = r;
		r = r->next;
		free(tmp);
	}
}

void	free_cmd(t_mini *m)
{
	t_cmd	*cmd;
	t_cmd	*prev;

	if (m->cmd)
		cmd = m->cmd;
	else
		cmd = NULL;
	while (cmd)
	{
		if (cmd->args)
			free_arr2(cmd->args);
		if (cmd->cmd_file)
			free(cmd->cmd_file);
		free_redir(cmd->redir);
		free_redir(cmd->l_redir);
		free_redir(cmd->r_redir);
		prev = cmd;
		cmd = cmd->next;
		free(prev);
	}
	m->cmd = cmd_lstnew();
}

void	free_while(char *line, t_mini *m)
{
	if (line)
		free(line);
	free_list(m);
	free_cmd(m);
}
