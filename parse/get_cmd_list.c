/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggoc <seonggoc@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:28:04 by seonggoc          #+#    #+#             */
/*   Updated: 2023/11/15 18:09:21 by seonggoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*make_redir(t_redir *redir, t_list *curr, int *dlft)
{
	char	*str;
	int		type;

	if (curr->type == DLFT)
		*dlft = 1;
	type = curr->type;
	curr = curr->next;
	while (curr && curr->type == SPCE)
	{
		curr = curr->next;
	}
	if (curr == NULL || curr->type != NORM)
		str = NULL;
	else
	{
		str = ft_strdup(curr->str);
	}
	add_redir(str, type, redir);
	return (curr);
}

char	**make_args(t_list *curr)
{
	int		size;
	char	**args;
	t_list	*tmp;

	tmp = curr;
	size = 1;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == NORM)
		{
			size++;
		}
		tmp = tmp->next;
	}
	args = (char **)malloc(sizeof(char *) * (size));
	return (args);
}

t_list	*make_cmd(t_cmd *cmd, t_list *curr, int is_pipe, t_redir *redir)
{
	int		i;
	int		dlft;
	char	**args;

	i = 0;
	dlft = 0;
	args = make_args(curr);
	while (curr && curr->type != PIPE)
	{
		if (RIGT <= curr->type)
		{
			if (redir == NULL)
				redir = lstnew_redir();
			curr = make_redir(redir, curr, &dlft);
		}
		else if (curr->type == NORM)
			args[i++] = ft_strdup(curr->str);
		if (curr != NULL)
			curr = curr->next;
	}
	args[i] = NULL;
	cmd_add_node(args, is_pipe, redir, cmd);
	get_last_cmd(cmd)->redir = redir;
	cmd->is_dlft = dlft;
	return (curr);
}

int	get_cmd_list_size(t_list *list)
{
	int	i;

	i = 1;
	while (list)
	{
		if (PIPE == list->type || DPIP == list->type)
		{
			i++;
		}
		list = list->next;
	}
	return (i);
}

void	get_cmd_list(t_mini *m)
{
	int		is_pipe;
	int		list_size;
	t_cmd	*last;
	t_list	*curr;
	t_redir	*redir;

	is_pipe = 1;
	curr = m->list;
	merge_norm(m->list);
	list_size = get_cmd_list_size(curr);
	while (list_size != 0)
	{
		if (list_size == 1)
			is_pipe = 0;
		last = get_last_cmd(m->cmd);
		redir = NULL;
		curr = make_cmd(last, curr, is_pipe, redir);
		if (curr)
			curr = curr->next;
		list_size--;
	}
}
