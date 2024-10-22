/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggoc <seonggoc@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 05:59:24 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/09 14:42:16 by seonggoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*init_envp(char **envp, int idx, int len)
{
	t_envp	*env;
	t_envp	*tmp;

	env = (t_envp *)malloc(sizeof(t_envp));
	if (!env)
		exit(1);
	env->prev = NULL;
	tmp = env;
	len = get_arr2_len(envp);
	idx = 0;
	while (idx < len)
	{
		env->str = ft_strdup(envp[idx]);
		env->dict = ft_split(envp[idx], '=');
		if (idx + 1 == len)
			env->next = NULL;
		else
		{
			env->next = (t_envp *)malloc(sizeof(t_envp));
			env->next->prev = env;
		}
		env = env->next;
		idx++;
	}
	return (tmp);
}

void	init(t_mini *m, char **envp)
{
	m->list = lstnew();
	m->cmd = cmd_lstnew();
	m->envp = init_envp(envp, 0, 0);
}
