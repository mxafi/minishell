/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:00:45 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/09 12:01:32 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_basic.h"

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
