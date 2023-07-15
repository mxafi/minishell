/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:06:07 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/13 16:54:37 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

/**
 * @brief Pushes the src element to the end of the dst vector.
 * 
 * @param dst the vector to be pushed into.
 * @param src the element to be added at the end of dst, limited by elem_size.
 * @return int - positive on success.
 */
int	vec_push(t_vec *dst, void *src)
{
	size_t	offset;
	size_t	required_size;
	size_t	i;

	if (!dst || !dst->memory || !src)
		return (-1);
	required_size = dst->elem_size * (dst->len + 1);
	if (dst->alloc_size < required_size)
	{
		if (vec_resize(dst, required_size) <= 0)
			return (-1);
	}
	offset = dst->elem_size * dst->len;
	i = 0;
	while (i < dst->elem_size)
	{
		dst->memory[offset + i] = ((unsigned char *)src)[i];
		i++;
	}
	dst->len++;
	return (1);
}
