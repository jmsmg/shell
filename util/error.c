/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:49:55 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/15 21:12:38 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern long long	g_exit_code;

void	str_error_handler(char *cmd, char *opt, char *str, int exit_code)
{
	printf("minishell: ");
	if (cmd)
		printf("%s: ", cmd);
	if (opt)
		printf("%s: ", opt);
	printf("%s\n", str);
	g_exit_code = exit_code;
}
