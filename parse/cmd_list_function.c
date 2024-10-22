/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_function.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggoc <seonggoc@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:28:02 by seonggoc          #+#    #+#             */
/*   Updated: 2023/11/15 17:20:16 by seonggoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*cmd_lstnew(void)
{
	t_cmd	*list;

	list = (t_cmd *)malloc(sizeof(t_cmd));
	if (!list)
		return (NULL);
	list->args = NULL;
	list->is_pipe = 0;
	list->infile_fd = -1;
	list->outfile_fd = -1;
	list->is_dlft = 0;
	list->cmd_file = NULL;
	list->redir = NULL;
	list->l_redir = NULL;
	list->r_redir = NULL;
	list->prev = NULL;
	list->next = NULL;
	return (list);
}

void	cmd_add_node(char **args, int is_pipe, t_redir *redir, t_cmd *cmd)
{
	t_cmd	*tmp;
	t_cmd	*last;

	if (cmd->args == NULL && cmd->redir == NULL)
	{
		cmd->args = args;
		cmd->is_pipe = is_pipe;
		cmd->redir = redir;
		return ;
	}
	last = get_last_cmd(cmd);
	tmp = cmd_lstnew();
	tmp->args = args;
	tmp->is_pipe = is_pipe;
	tmp->infile_fd = -1;
	tmp->outfile_fd = -1;
	tmp->is_dlft = 0;
	tmp->cmd_file = NULL;
	tmp->redir = redir;
	tmp->next = NULL;
	tmp->prev = last;
	last->next = tmp;
}
