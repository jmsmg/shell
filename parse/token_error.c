/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:30:08 by seonggoc          #+#    #+#             */
/*   Updated: 2023/11/14 21:07:47 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe_error(t_list *curr, t_list *next, t_list *last, char *tmp)
{
	if (curr->type == DPIP)
	{
		str_error_handler("|", NULL, "syntax error near unexpected token", 258);
		return (1);
	}
	if (last->type == LEFT || last->type == DLFT)
	{
		tmp = last->str;
		str_error_handler(tmp, NULL, "syntax error near unexpected token", 258);
		return (1);
	}
	if (PIPE <= curr->type && (next && next->type == PIPE))
	{
		tmp = next->str;
		str_error_handler(tmp, NULL, "syntax error near unexpected token", 258);
		return (1);
	}
	return (0);
}

int	check_parse_error(t_list *curr, t_list *last, char *tmp)
{
	t_list	*next;

	next = curr->next;
	if (curr->type == PIPE)
	{
		str_error_handler("|", NULL, "syntax error near unexpected token", 258);
		return (1);
	}
	while (curr)
	{
		if (PIPE == curr->type && (next && next->type == LEFT))
			continue ;
		if (check_pipe_error(curr, next, last, tmp))
			return (1);
		curr = curr->next;
		if (curr)
			next = curr->next;
	}
	if (PIPE <= last->type)
	{
		tmp = last->str;
		str_error_handler(tmp, NULL, "syntax error near unexpected token", 258);
		return (1);
	}
	return (0);
}

int	token_error(t_mini *m, t_parse *par)
{
	char	*tmp;
	t_list	*curr;
	t_list	*last;

	tmp = NULL;
	curr = m->list;
	last = get_last_list(curr);
	if (par->quote != 0)
	{
		str_error_handler("'", NULL, "The number of quotes does not match", 1);
		return (1);
	}
	if (m->list->str == NULL)
		return (1);
	if (check_parse_error(curr, last, tmp))
		return (1);
	return (0);
}
