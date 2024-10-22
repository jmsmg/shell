/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:28:08 by seonggoc          #+#    #+#             */
/*   Updated: 2023/11/15 21:10:55 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern long long	g_exit_code;

int	compare_str(const char *haystack, const char *needle)
{
	while (*needle || *haystack)
	{
		if (*haystack != *needle)
			return (0);
		haystack++;
		needle++;
	}
	return (1);
}

char	*trans_str(t_envp *envp, char *str)
{
	char	*tmp;

	tmp = "";
	if (*str == '\0')
	{
		tmp = ft_strdup("$");
		return (tmp);
	}
	while (envp->next)
	{
		if (compare_str(str, (envp->dict)[0]))
		{
			tmp = ft_strdup((envp->dict)[1]);
			return (tmp);
		}
		envp = envp->next;
	}
	if (compare_str(str, (envp->dict)[0]))
	{
		tmp = ft_strdup((envp->dict)[1]);
		return (tmp);
	}
	return (tmp);
}

char	*process_dollar_sign(t_mini *m, char *str, int *i, char *chunk)
{
	int		j;
	char	*before;
	char	*tmp;
	char	*after;

	j = 0;
	while (str[*i + j] && str[*i + j] != '$'
		&& (('A' <= str[*i + j] && str[*i + j] <= 'Z')
			|| ('a' <= str[*i + j] && str[*i + j] <= 'z')))
		j++;
	tmp = ft_strndup(str + *i, j);
	before = trans_str(m->envp, tmp);
	free(tmp);
	*i += j - 1;
	after = ft_strjoin(chunk, before);
	free(before);
	free(chunk);
	return (after);
}

char	*get_prev_exit_code(char *chunk)
{
	char	*tmp;
	char	*ret;

	tmp = ft_itoa(g_exit_code);
	ret = ft_strjoin(chunk, tmp);
	free(chunk);
	free(tmp);
	return (ret);
}

char	*get_chunk_str(t_mini *m, char *str)
{
	int		i;
	char	*chunk;

	i = 0;
	chunk = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '?')
				chunk = get_prev_exit_code(chunk);
			else
				chunk = process_dollar_sign(m, str, &i, chunk);
		}
		else
		{
			chunk = ft_strjoin_char(chunk, str[i]);
		}
		i++;
	}
	free(str);
	return (chunk);
}
