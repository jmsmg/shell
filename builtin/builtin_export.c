/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 23:44:55 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/14 17:53:04 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(t_mini *m, char **key_value)
{
	t_envp	*envp;
	char	*tmp;

	envp = m->envp;
	while (envp)
	{
		if (!ft_strcmp(envp->dict[0], key_value[0]))
		{
			free(envp->dict[1]);
			envp->dict[1] = ft_strdup(key_value[1]);
			free(envp->str);
			envp->str = ft_strjoin(envp->dict[0], "=");
			tmp = envp->str;
			envp->str = ft_strjoin(envp->str, envp->dict[1]);
			free(tmp);
			break ;
		}
		envp = envp->next;
	}
}

void	push_env(t_mini *m, char **key_value)
{
	t_envp	*envp;
	char	*tmp;

	envp = get_last_envp(m);
	envp->next = (t_envp *)malloc(sizeof(t_envp));
	if (!envp->next)
		exit(1);
	envp->next->prev = envp;
	envp = envp->next;
	envp->dict = (char **)malloc(sizeof(char *) * 3);
	if (!envp->dict)
		exit(1);
	envp->dict[0] = ft_strdup(key_value[0]);
	envp->dict[1] = ft_strdup(key_value[1]);
	envp->dict[2] = NULL;
	envp->next = NULL;
	envp->str = ft_strjoin(envp->dict[0], "=");
	tmp = envp->str;
	envp->str = ft_strjoin(envp->str, envp->dict[1]);
	free(tmp);
}

char	**make_key_value(char	*str)
{
	char	**key_value;
	char	**tmp;

	key_value = ft_split(str, '=');
	if (get_arr2_len(key_value) != 2)
	{
		tmp = (char **)malloc(sizeof(char *) * 3);
		tmp[0] = ft_strdup(key_value[0]);
		tmp[1] = ft_strdup("");
		tmp[2] = NULL;
		free_arr2(key_value);
		key_value = tmp;
	}
	return (key_value);
}

void	do_env_printf(t_mini *m)
{
	t_envp	*envp;

	envp = m->envp;
	while (envp)
	{
		printf("declare -x %s=\"%s\"\n", envp->dict[0], envp->dict[1]);
		envp = envp->next;
	}
}

void	builtin_export(t_mini *m, t_cmd *cmd)
{
	char	**key_value;
	int		idx;

	if (get_arr2_len(cmd->args) == 1)
		do_env_printf(m);
	else if (get_arr2_len(cmd->args) >= 2)
	{
		idx = 1;
		while (cmd->args[idx])
		{
			if (ft_strchr(cmd->args[idx], '='))
			{
				key_value = make_key_value(cmd->args[idx]);
				if (is_env(m, key_value[0]))
					set_env(m, key_value);
				else
					push_env(m, key_value);
				free_arr2(key_value);
			}
			idx++;
		}
	}
}
