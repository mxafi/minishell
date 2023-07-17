/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:48:37 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/09 12:02:56 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

# include "../libft.h"

# include "ft_printf_utils.h"
# include "ft_printf_spec_hex.h"

int		ft_printf(const char *input, ...);

#endif
