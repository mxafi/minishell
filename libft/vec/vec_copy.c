/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:26:52 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/12 17:03:58 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

/**
 * @brief Copies src vector into dst vector, limited by dst alloc_size.
 * 
 * @param dst the destination vector, already created.
 * @param src the source vector
 * @return int - positive int on success
 */
int	vec_copy(t_vec *dst, t_vec *src)
{
	size_t	i;

	i = 0;
	if (!dst || !src)
		return (-1);
	while (i < dst->alloc_size && i < src->alloc_size)
	{
		dst->memory[i] = src->memory[i];
		i++;
	}
	return (1);
}
