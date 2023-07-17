/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:11:11 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/09 12:15:31 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_basic.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*new_s;

	if (!s)
		return (0);
	i = ft_strlen(s);
	new_s = malloc(i + 1);
	if (!new_s)
		return (0);
	new_s[i] = '\0';
	if (!*s)
		return (new_s);
	i--;
	while (i)
	{
		new_s[i] = f((unsigned int)i, s[i]);
		i--;
	}
	new_s[i] = f((unsigned int)i, s[i]);
	return (new_s);
}
