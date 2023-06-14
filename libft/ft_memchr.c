/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 12:08:22 by malaakso          #+#    #+#             */
/*   Updated: 2022/10/29 15:44:38 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
