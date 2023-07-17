/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_from.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:45:52 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/15 15:42:42 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
#include "../libft.h"

/**
 * @brief Copies data from memory to a new vector.
 * 
 * @param dst pointer to destination vector
 * @param src pointer to some memory
 * @param len element count
 * @param elem_size element size in bytes
 * @return int positive value on success
 */
int	vec_from(t_vec *dst, void *src, size_t len, size_t elem_size)
{
	if (!dst || !src || elem_size == 0)
		return (-1);
	if (vec_new(dst, len, elem_size) < 0)
		return (-1);
	ft_memmove(dst->memory, src, dst->alloc_size);
	dst->len = len;
	return (1);
}
