/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:02:11 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/15 16:57:33 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
#include "../libft.h"

/**
 * @brief Removes an element from desired index in the vector without
 * overwriting existing elements.
 * @param src the vector to remove an element from.
 * @param index the index of the element to be removed.
 * @return int - positive on success, negative on failure or when empty vector.
 */
int	vec_remove(t_vec *src, size_t index)
{
	if (!src || !src->memory || index >= src->len)
		return (-1);
	if (index == src->len - 1)
	{
		if (vec_pop(NULL, src) <= 0)
			return (-1);
		return (1);
	}
	ft_memmove(&src->memory[src->elem_size * index],
		&src->memory[src->elem_size * (index + 1)],
		src->elem_size * (src->len - index - 1));
	src->len--;
	if (vec_resize(src, src->alloc_size - src->elem_size) <= 0)
		return (-1);
	return (1);
}
