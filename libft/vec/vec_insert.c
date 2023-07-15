/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:57:13 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/15 16:01:00 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
#include "../libft.h"

/**
 * @brief Inserts a new element at desired index in the vector without
 * overwriting existing elements.
 * @param dst the destination vector.
 * @param src the element to be inserted.
 * @param index the index where the element will be inserted.
 * @return int - positive on success.
 */
int	vec_insert(t_vec *dst, void *src, size_t index)
{
	if (!src || !dst || !dst->memory || index > dst->len)
		return (-1);
	if (index == dst->len)
	{
		if (vec_push(dst, src) <= 0)
			return (-1);
		return (1);
	}
	if (vec_resize(dst, dst->alloc_size + dst->elem_size) <= 0)
		return (-1);
	ft_memmove(&dst->memory[dst->elem_size * (index + 1)],
		&dst->memory[dst->elem_size * index],
		dst->elem_size * (dst->len - index));
	ft_memmove(&dst->memory[dst->elem_size * index], src, dst->elem_size);
	dst->len++;
	return (1);
}
