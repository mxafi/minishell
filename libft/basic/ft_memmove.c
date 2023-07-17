/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:28:26 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/09 12:13:27 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_basic.h"

static void	*ft_memcpyr(void *dst, const void *src, size_t n)
{
	while (n > 0)
	{
		((char *)dst)[n - 1] = ((char *)src)[n - 1];
		n--;
	}
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst < src)
	{
		ft_memcpy(dst, src, len);
	}
	else if (dst > src)
	{
		ft_memcpyr(dst, src, len);
	}
	return (dst);
}
