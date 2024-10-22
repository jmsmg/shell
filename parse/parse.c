/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:28:11 by seonggoc          #+#    #+#             */
/*   Updated: 2023/11/15 21:10:43 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern long long	g_exit_code;

void	get_chunk(t_parse *par, char *line, t_mini *m)
{
	int		type;
	char	curr;
	char	*chunk;

	curr = line[par->i];
	type = check_str_type(curr);
	if (curr == '\'' || curr == '\"')
		get_chunk_index(par, line, 1);
	else
		get_chunk_index(par, line, 0);
	if (par->quote == 0 && (type == SINQ))
	{
		chunk = ft_strndup(line + par->start + 1, par->i - par->start - 2);
	}
	else if (par->quote == 0 && (type == DOUQ))
	{
		chunk = ft_strndup(line + par->start + 1, par->i - par->start - 2);
		chunk = get_chunk_str(m, chunk);
	}
	else
	{
		chunk = ft_strndup(line + par->start, par->i - par->start);
		chunk = get_chunk_str(m, chunk);
	}
	add_node(chunk, NORM, m->list);
}

void	get_redirection(t_parse *par, char *line, t_mini *m)
{
	char	curr;
	char	next;

	curr = line[par->i];
	next = line[par->i + 1];
	if (curr != next)
		get_single_character(par, line, m);
	else
	{
		if (line[par->i] == '|')
			add_node(ft_strdup("||"), DPIP, m->list);
		else if (line[par->i] == '>')
			add_node(ft_strdup(">>"), DRGT, m->list);
		else if (line[par->i] == '<')
			add_node(ft_strdup("<<"), DLFT, m->list);
		par->start += 2;
		par->i += 2;
	}
}

void	get_single_character(t_parse *par, char *line, t_mini *m)
{
	if (line[par->i] == ' ')
		add_node(ft_strdup(" "), SPCE, m->list);
	if (line[par->i] == '|')
		add_node(ft_strdup("|"), PIPE, m->list);
	if (line[par->i] == '>')
		add_node(ft_strdup(">"), RIGT, m->list);
	if (line[par->i] == '<')
		add_node(ft_strdup("<"), LEFT, m->list);
	par->start++;
	par->i++;
}

void	parse_sequence(t_mini *m, t_parse *par, int type, char *line)
{
	while (line[par->i])
	{
		type = check_cmd_type(line[par->i]);
		if (type == SINGL)
			get_single_character(par, line, m);
		else if (type == REDIR)
			get_redirection(par, line, m);
		else if (type == CHUNK)
		{
			get_chunk(par, line, m);
			if (line[par->i] != '\0')
				par->start = par->i;
		}
		if (line[par->i] == '\0')
			break ;
	}
}

int	parse(char *line, t_mini *m)
{
	int		type;
	char	*tmp;
	t_parse	par;

	tmp = NULL;
	type = CHUNK;
	par = (t_parse){.i = 0, .start = 0, .quote = 0};
	parse_sequence(m, &par, type, line);
	get_cmd_list(m);
	make_redir_l_r(m->cmd, tmp);
	if (check_redir_str(m->cmd->redir) || token_error(m, &par))
		return (-1);
	g_exit_code = 0;
	return (get_cmd_list_size(m->list) - 1);
}
