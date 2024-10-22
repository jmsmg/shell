/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:10:18 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/03 17:10:19 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(void)
{
	char	*cur_dir;

	cur_dir = getcwd(NULL, 0);
	ft_putstr_fd(cur_dir, 1);
	write(1, "\n", 1);
	free(cur_dir);
}
