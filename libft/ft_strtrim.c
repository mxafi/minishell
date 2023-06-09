/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:38:23 by malaakso          #+#    #+#             */
/*   Updated: 2022/11/04 16:02:11 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] && set[i] != c)
		i++;
	if (c != '\0' && set[i] == '\0')
		return (0);
	return (1);
}

static int	ret_trim_index(char *s1, size_t *t_f, size_t *t_b, char *set)
{
	*t_f = 0;
	while (is_in_set(s1[*t_f], set) && s1[*t_f])
		(*t_f)++;
	*t_b = ft_strlen(s1);
	if (!*t_b)
		return (1);
	(*t_b)--;
	while (is_in_set(s1[*t_b], set) && *t_b != 0)
		(*t_b)--;
	if (*t_f > *t_b)
		return (1);
	return (0);
}

static char	*set_copy(size_t size)
{
	char	*copy;

	if (!size)
		return (0);
	copy = malloc(size);
	if (!copy)
		return (0);
	copy[size - 1] = 0;
	return (copy);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*copy;
	size_t	trim_front;
	size_t	trim_back;
	size_t	offset;

	if (!s1 || !set)
		return (0);
	if (ret_trim_index((char *)s1, &trim_front, &trim_back, (char *)set))
	{
		copy = set_copy(1);
		if (!copy)
			return (0);
		return (copy);
	}
	copy = set_copy(trim_back - trim_front + 2);
	if (!copy)
		return (0);
	offset = trim_front;
	while (trim_front <= trim_back)
	{
		copy[trim_front - offset] = s1[trim_front];
		trim_front++;
	}
	return (copy);
}
