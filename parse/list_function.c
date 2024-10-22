/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggoc <seonggoc@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:28:06 by seonggoc          #+#    #+#             */
/*   Updated: 2023/11/07 13:28:07 by seonggoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*lstnew(void)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->str = NULL;
	list->type = 0;
	list->next = NULL;
	return (list);
}

void	add_node(char *str, int type, t_list *list)
{
	t_list	*next;

	if (list->str == NULL)
	{
		list->str = str;
		list->type = type;
		list->next = NULL;
		return ;
	}
	next = lstnew();
	list = get_last_list(list);
	next->str = str;
	next->type = type;
	list->next = next;
}

t_redir	*lstnew_redir(void)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->str = NULL;
	redir->type = 0;
	redir->next = NULL;
	return (redir);
}

void	add_redir(char *str, int type, t_redir *redir)
{
	t_redir	*tmp;

	if (redir->type == 0)
	{
		redir->str = str;
		redir->type = type;
		redir->next = NULL;
		return ;
	}
	tmp = lstnew_redir();
	redir = get_last_redir(redir);
	tmp->str = str;
	tmp->type = type;
	redir->next = tmp;
}
