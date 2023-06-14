/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:47:02 by malaakso          #+#    #+#             */
/*   Updated: 2022/11/26 02:02:34 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	resolve_specifier_2(const char *specifier, va_list args)
{
	int	count;

	count = 0;
	if (*specifier == 'p' || *specifier == 'x' || *specifier == 'X')
		count = resolve_specifier_hex(specifier, args);
	return (count);
}

static int	resolve_specifier_1(const char *specifier, va_list args)
{
	int	count;

	count = 0;
	if (*specifier == '%')
		count = ft_int_putchar_fd('%', 1);
	else if (*specifier == 'c')
		count = ft_int_putchar_fd((char)va_arg(args, int), 1);
	else if (*specifier == 's')
	{
		count = ft_int_putstr_fd(va_arg(args, char *), 1);
		if (count == -1)
			count = ft_int_putstr_fd("(null)", 1);
	}
	else if (*specifier == 'd')
		count = ft_int_putnbr_fd(va_arg(args, int), 1);
	else if (*specifier == 'i')
		count = ft_int_putnbr_fd(va_arg(args, int), 1);
	else if (*specifier == 'u')
		count = ft_int_putnbr_uint_fd((unsigned int)va_arg(args, unsigned int),
				1);
	else
		count = resolve_specifier_2(specifier, args);
	return (count);
}

int	ft_printf(const char *input, ...)
{
	va_list	args;
	long	n_of_characters_printed;

	va_start(args, input);
	n_of_characters_printed = 0;
	while (*input)
	{
		while (*input != '%')
		{
			n_of_characters_printed += ft_int_putchar_fd(*input, 1);
			input++;
			if (!*input)
				break ;
		}
		if (*input == '%')
		{
			input++;
			n_of_characters_printed += resolve_specifier_1(input, args);
		}
		if (!*input)
			break ;
		input++;
	}
	va_end(args);
	return ((int)n_of_characters_printed);
}
