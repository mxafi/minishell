/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:27:14 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/14 15:35:07 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

/**
 * @brief Return an opaque handle to the element at index.
 * 
 * @param src the source vector.
 * @param index the index of the desired element. 
 * @return void* - a pointer to the desired element in the vector's memory.
 */
void	*vec_get(t_vec *src, size_t index)
{
	if (!src || !src->memory || index >= src->len)
		return (NULL);
	return (&src->memory[src->elem_size * index]);
}
