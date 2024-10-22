/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:30:52 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/08 16:48:29 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_home(t_mini *m)
{
	t_envp	*envp;

	envp = m->envp;
	while (envp)
	{
		if (!ft_strcmp("HOME", envp->dict[0]))
			return (ft_strdup(envp->dict[1]));
		envp = envp->next;
	}
	return (NULL);
}

t_envp	*get_envp(t_envp *envp, char *str)
{
	while (envp)
	{
		if (!ft_strcmp(str, envp->dict[0]))
			return (envp);
		envp = envp->next;
	}
	return (NULL);
}

char	*make_env_str(char *str1, char *str2)
{
	char	*str;
	char	*tmp;

	str = ft_strjoin(str1, "=");
	tmp = ft_strjoin(str, str2);
	free(str);
	return (tmp);
}

void	make_oldpwd(t_mini *m, char *now)
{
	t_envp	*envp;
	char	*str;

	str = make_env_str("OLDPWD", now);
	envp = get_envp(m->envp, "OLDPWD");
	if (envp)
	{
		if (envp->dict && envp->dict[1])
			free(envp->dict[1]);
		envp->dict[1] = ft_strdup(now);
		if (envp->str)
			free(envp->str);
		envp->str = str;
	}
	else
	{
		envp = get_last_envp(m);
		envp->next = (t_envp *)malloc(sizeof(t_envp));
		if (!envp->next)
			str_error_handler("Malloc", NULL, "Insufficient Memory", 1);
		envp->next->str = str;
		envp->next->dict = ft_split(str, '=');
		envp->next->prev = envp;
		envp->next->next = NULL;
	}
}
