/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_norm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggoc <seonggoc@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:20:04 by seonggoc          #+#    #+#             */
/*   Updated: 2023/11/15 17:26:10 by seonggoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	merge_norm(t_list *list)
{
	char	*str;
	t_list	*curr;
	t_list	*next;

	curr = list;
	next = curr->next;
	while (next)
	{
		if (curr->type == NORM && next->type == NORM)
		{
			str = ft_strjoin(curr->str, next->str);
			free(curr->str);
			curr->str = str;
			free(next->str);
			curr->next = next->next;
			free(next);
			next = curr->next;
		}
		else
		{
			curr = curr->next;
			next = curr->next;
		}
	}
}

void	make_redir_l_r(t_cmd *curr, char *tmp)
{
	t_redir	*redir;

	while (curr)
	{
		redir = curr->redir;
		while (redir)
		{
			if (redir->str)
				tmp = ft_strdup(redir->str);
			if (redir->type == LEFT || redir->type == DLFT)
			{
				if (curr->l_redir == NULL)
					curr->l_redir = lstnew_redir();
				add_redir(tmp, redir->type, curr->l_redir);
			}
			else if (redir->type == RIGT || redir->type == DRGT)
			{
				if (curr->r_redir == NULL)
					curr->r_redir = lstnew_redir();
				add_redir(tmp, redir->type, curr->r_redir);
			}
			redir = redir->next;
		}
		curr = curr->next;
	}
}
