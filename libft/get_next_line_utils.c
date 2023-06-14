/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:08:44 by malaakso          #+#    #+#             */
/*   Updated: 2022/12/15 13:26:29 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*p;
	size_t	i;

	p = ft_calloc(n + 1, 1);
	if (!p)
		return (0);
	p[n] = '\0';
	i = 0;
	while (s1[i] && i < n)
	{
		p[i] = s1[i];
		i++;
	}
	return (p);
}
