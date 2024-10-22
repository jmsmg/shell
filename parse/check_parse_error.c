/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggoc <seonggoc@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:27:59 by seonggoc          #+#    #+#             */
/*   Updated: 2023/11/15 17:24:29 by seonggoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_str_type(char curr)
{
	int	type;

	type = 0;
	if (curr == '\'')
		type = SINQ;
	else if (curr == '\"')
		type = DOUQ;
	else
		type = NORM;
	return (type);
}

int	check_cmd_type(char line)
{
	if (line == ' ')
		return (SINGL);
	else if (line == '|' || line == '<' || line == '>')
		return (REDIR);
	else
		return (CHUNK);
}

void	ret_redir_string(t_redir *redir)
{
	char	*red;
	char	*str;

	str = "parse error near unexpected token";
	red = NULL;
	if (redir->next)
	{
		if (redir->next->type == RIGT)
			red = ">";
		else if (redir->next->type == DRGT)
			red = ">>";
		else if (redir->next->type == LEFT)
			red = "<<";
		else if (redir->next->type == DLFT)
			red = "<<";
		str_error_handler(red, NULL, str, 258);
	}
	else
		str_error_handler("newline", NULL, str, 258);
}

int	check_redir_str(t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (!(tmp->str))
		{
			ret_redir_string(tmp);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
