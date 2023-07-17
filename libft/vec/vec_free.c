/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:44:23 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/15 17:05:46 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

/**
 * @brief Frees the specified vector's memory and nulls its values.
 * Note that the pointer to the vector struct is not freed, as it's meant
 * to exist in stack memory.
 * @param src the specified vector to be freed.
 */
void	vec_free(t_vec *src)
{
	if (!src)
		return ;
	if (src->memory)
		free(src->memory);
	src->memory = NULL;
	src->alloc_size = 0;
	src->elem_size = 0;
	src->len = 0;
}
