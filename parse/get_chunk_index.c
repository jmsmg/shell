/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_chunk_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggoc <seonggoc@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:15:09 by seonggoc          #+#    #+#             */
/*   Updated: 2023/11/14 13:15:27 by seonggoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_chunk_index(t_parse *par, char *line, int type)
{
	if (type == 0)
	{
		while (line[par->i] && line[par->i] != ' ' && line[par->i] != '\"'
			&& line[par->i] != '|' && line[par->i] != '<' && line[par->i] != '>'
			&& line[par->i] != '\'')
		{
			par->i++;
		}
	}
	else
	{
		par->quote = 1;
		par->i++;
		while (line[par->i] && line[par->start] != line[par->i])
			par->i++;
		if (line[par->i])
		{
			par->quote = 0;
			par->i++;
		}
	}
}
