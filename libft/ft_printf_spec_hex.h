/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_spec_hex.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 23:59:40 by malaakso          #+#    #+#             */
/*   Updated: 2022/11/26 02:02:20 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_SPEC_HEX_H
# define FT_PRINTF_SPEC_HEX_H

# include "ft_printf.h"

int	resolve_specifier_hex(const char *specifier, va_list args);

#endif