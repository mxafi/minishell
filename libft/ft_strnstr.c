/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:16:29 by malaakso          #+#    #+#             */
/*   Updated: 2022/11/10 15:25:57 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ret_found(char *p, const char *needle, size_t len)
{
	char	*len_addr;
	size_t	n_len;
	size_t	p_len;

	len_addr = p + len - 1;
	n_len = ft_strlen(needle);
	while (*p && p <= len_addr)
	{
		p = ft_strchr(p, needle[0]);
		if (!p)
			return (0);
		p_len = (size_t)len_addr - (size_t)p + 1;
		if ((p_len >= n_len) && p_len <= len)
		{
			if (!ft_strncmp(p, needle, n_len))
				return (p);
		}
		p++;
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*p;
	size_t	hs_len;

	p = (char *)haystack;
	if (*needle == '\0')
		return (p);
	if (!len)
		return (0);
	hs_len = ft_strlen(haystack);
	if (len > hs_len)
		len = hs_len;
	return (ret_found(p, needle, len));
}
