/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_spec_hex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 23:47:51 by malaakso          #+#    #+#             */
/*   Updated: 2022/11/26 02:02:31 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_int_puthex_lower_fd(unsigned long n, int fd)
{
	int				count;
	int				remainder;
	char			hex[64];

	count = 0;
	while (n && count < 64)
	{
		remainder = n % 16;
		if (remainder < 10)
			remainder += '0';
		else
			remainder += 87;
		n /= 16;
		hex[count] = (char)remainder;
		count++;
	}
	hex[count] = '\0';
	(void)ft_strrev(hex);
	count = 0;
	if (*hex == '\0')
		count += ft_int_putchar_fd('0', fd);
	count += ft_int_putstr_fd(hex, fd);
	return (count);
}

static int	ft_int_puthex_upper_fd(unsigned long n, int fd)
{
	int				count;
	int				remainder;
	char			hex[64];

	count = 0;
	while (n && count < 64)
	{
		remainder = n % 16;
		if (remainder < 10)
			remainder += '0';
		else
			remainder += 55;
		n /= 16;
		hex[count] = (char)remainder;
		count++;
	}
	hex[count] = '\0';
	(void)ft_strrev(hex);
	count = 0;
	if (*hex == '\0')
		count += ft_int_putchar_fd('0', fd);
	count += ft_int_putstr_fd(hex, fd);
	return (count);
}

int	resolve_specifier_hex(const char *specifier, va_list args)
{
	int	count;

	count = 0;
	if (*specifier == 'p')
	{
		count = ft_int_putstr_fd("0x", 1);
		count += ft_int_puthex_lower_fd((unsigned long)va_arg(args, void *), 1);
	}
	else if (*specifier == 'x')
		count = ft_int_puthex_lower_fd((unsigned long)va_arg(args,
					unsigned int), 1);
	else if (*specifier == 'X')
		count = ft_int_puthex_upper_fd((unsigned long)va_arg(args,
					unsigned int), 1);
	return (count);
}
