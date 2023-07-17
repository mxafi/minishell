/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:40:39 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/09 12:15:31 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_basic.h"

char	*ft_strdup(const char *s1)
{
	size_t	s1_len;
	char	*p;
	size_t	i;

	s1_len = ft_strlen(s1);
	p = malloc(s1_len + 1);
	if (!p)
		return (0);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = 0;
	return (p);
}
