/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungmin <seungmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:38:42 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/02 16:19:28 by seungmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strcat(char *s, const char *s1, const char *s2)
{
	size_t	idx;

	idx = 0;
	while (idx < ft_strlen(s1))
	{
		s[idx] = s1[idx];
		idx++;
	}
	s[idx] = ' ';
	idx = 0;
	while (idx < ft_strlen(s2) + 1)
	{
		s[ft_strlen(s1) + 1 + idx] = s2[idx];
		idx++;
	}
	s[ft_strlen(s1) + idx] = '\0';
	return (s);
}

char	*ft_newjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*s;

	if (!ft_strlen(s1) && !ft_strlen(s2))
		return ((char *)ft_calloc(sizeof(char), 1));
	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	s = (char *) malloc(sizeof(char) * len);
	if (!s)
		return (NULL);
	return (ft_strcat(s, s1, s2));
}
