/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:07:24 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/03 18:07:59 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_envp_len(t_mini *m)
{
	t_envp	*envp;
	int		len;

	envp = NULL;
	if (m->envp)
		envp = m->envp;
	len = 0;
	while (envp)
	{
		len++;
		envp = envp->next;
	}
	return (len);
}

char	**make_envp(t_mini *m)
{
	t_envp	*envp;
	char	**result;
	int		len;
	int		idx;

	if (m->envp)
		envp = m->envp;
	len = get_envp_len(m);
	result = (char **)malloc(sizeof(char *) * (len + 1));
	idx = 0;
	while (idx < len)
	{
		result[idx] = envp->str;
		idx++;
		envp = envp->next;
	}
	result[idx] = NULL;
	return (result);
}
