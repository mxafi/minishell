/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:05:23 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/13 15:53:31 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

/**
 * @brief Initializes a new vector.
 * 
 * @param dst pointer to declared t_vec.
 * @param init_len how many elements can the vector fit right initially.
 * @param elem_size size of an element in bytes.
 * @return int - positive value on success
 */
int	vec_new(t_vec *dst, size_t init_len, size_t elem_size)
{
	if (!dst || elem_size == 0)
		return (-1);
	dst->elem_size = elem_size;
	dst->len = 0;
	dst->alloc_size = init_len * elem_size;
	if (init_len > 0)
	{
		dst->memory = malloc(sizeof(unsigned char) * dst->alloc_size);
		if (!dst->memory)
			return (-1);
	}
	else if (init_len == 0)
		dst->memory = NULL;
	else
		return (-1);
	return (1);
}
