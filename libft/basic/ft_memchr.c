/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 12:08:22 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/09 12:15:31 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_basic.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	size_t			i;

	if (!n)
		return (NULL);
	p = (unsigned char *)s;
	i = 0;
	while ((i < (n - 1)) && *p != (unsigned char)c)
	{
		p++;
		i++;
	}
	if (*p == (unsigned char)c)
		return (p);
	return (NULL);
}
