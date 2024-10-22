/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggoc <seonggoc@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 02:32:40 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/14 16:51:55 by seonggoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_option(char *str)
{
	int	idx;

	if (!(str && str[0] == '-'))
		return (0);
	idx = 1;
	while (str[idx])
	{
		if (str[idx] != 'n')
			return (0);
		idx++;
	}
	return (1);
}

void	builtin_echo(t_cmd *cmd)
{
	int		flag;
	int		idx;
	int		opt;
	int		str_cnt;

	opt = 0;
	flag = 0;
	str_cnt = 0;
	idx = 1;
	while (cmd->args[idx])
	{
		if (is_option(cmd->args[idx]) && flag == 0)
			opt++;
		else
		{
			flag = 1;
			if (str_cnt != 0)
				ft_putstr_fd(" ", 1);
			ft_putstr_fd(cmd->args[idx], 1);
			str_cnt++;
		}
		idx++;
	}
	if (!opt)
		ft_putstr_fd("\n", 1);
}
