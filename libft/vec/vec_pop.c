/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_pop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:58:48 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/13 17:17:31 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

/**
 * @brief Removes last element from a given vector, copies element to dst.
 * 
 * @param dst desired output for the popped element, can be NULL.
 * @param src target vector from which to remove the last element.
 * @return int - positive value on success.
 */
int	vec_pop(void *dst, t_vec *src)
{
	size_t	offset;
	size_t	new_size;
	size_t	i;

	if (!src)
		return (-1);
	if (src->len == 0)
		return (1);
	if (dst)
	{
		offset = src->elem_size * (src->len - 1);
		i = 0;
		while (i < src->elem_size)
		{
			((unsigned char *)dst)[i] = src->memory[offset + i];
			i++;
		}
	}
	new_size = src->alloc_size - src->elem_size;
	if (vec_resize(src, new_size) <= 0)
		return (-1);
	src->len--;
	return (1);
}
