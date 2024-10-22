/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:08:07 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/15 19:19:39 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern long long	g_exit_code;

void	check_validation(int argc, char **argv)
{
	if (argc != 1 && ft_strnstr(argv[0], "./minishell", 11))
	{
		str_error_handler(argv[0], NULL,
			"Please, Run Minishell Without Arguments", 1);
		exit(g_exit_code);
	}
}
