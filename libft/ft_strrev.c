/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 00:13:35 by malaakso          #+#    #+#             */
/*   Updated: 2022/11/26 00:46:52 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *s)
{
	size_t	s_len;
	char	*tmp;
	char	*orig_tmp;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= 1)
		return (s);
	tmp = ft_strdup(s);
	if (!tmp)
		return (NULL);
	orig_tmp = tmp;
	while (s_len > 0)
	{
		s[s_len - 1] = *tmp;
		tmp++;
		s_len--;
	}
	free(orig_tmp);
	return (s);
}
