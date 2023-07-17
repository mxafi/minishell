/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:48:07 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/09 13:19:32 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_UTILS_H
# define FT_PRINTF_UTILS_H

# include <unistd.h>

int	ft_int_putchar_fd(char c, int fd);
int	ft_int_putstr_fd(char *s, int fd);
int	ft_int_putnbr_fd(int n, int fd);
int	ft_int_putnbr_uint_fd(unsigned int n, int fd);

#endif
