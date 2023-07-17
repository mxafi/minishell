/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_resize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 06:55:11 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/13 16:44:59 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

/**
 * @brief Shrinks destructively or grows the given vector to target size.
 * 
 * @param src the vector to reallocate.
 * @param target_size the desired size in bytes.
 * @return int - positive value on success, negative on failure
 */
int	vec_resize(t_vec *src, size_t target_size)
{
	t_vec	tmp;

	if (!src)
		return (-1);
	if (src->alloc_size == target_size)
		return (1);
	tmp.alloc_size = target_size;
	tmp.elem_size = src->elem_size;
	tmp.len = src->len;
	tmp.memory = malloc(target_size);
	if (!tmp.memory || vec_copy(&tmp, src) <= 0)
	{
		vec_free(&tmp);
		return (-1);
	}
	vec_free(src);
	src->alloc_size = tmp.alloc_size;
	src->elem_size = tmp.elem_size;
	src->len = tmp.len;
	src->memory = tmp.memory;
	return (1);
}
