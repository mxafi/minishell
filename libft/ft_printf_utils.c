/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:47:21 by malaakso          #+#    #+#             */
/*   Updated: 2023/03/19 15:35:55 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_int_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_int_putstr_fd(char *s, int fd)
{
	size_t	i;
	int		count;

	count = 0;
	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		count += ft_int_putchar_fd(s[i], fd);
		i++;
	}
	return (count);
}

int	ft_int_putnbr_fd(int n, int fd)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		if (n == -2147483648)
		{
			count += ft_int_putchar_fd('-', fd);
			count += ft_int_putchar_fd('2', fd);
			n = 147483648;
		}
		else
		{
			count += ft_int_putchar_fd('-', fd);
			count += ft_int_putnbr_fd(n * -1, fd);
		}
	}
	if (n > 9)
	{
		count += ft_int_putnbr_fd(n / 10, fd);
		count += ft_int_putnbr_fd(n % 10, fd);
	}
	if (n >= 0 && n < 10)
		count += ft_int_putchar_fd((char)n + '0', fd);
	return (count);
}

int	ft_int_putnbr_uint_fd(unsigned int n, int fd)
{
	int	count;

	count = 0;
	if (n > 9)
	{
		count += ft_int_putnbr_fd(n / 10, fd);
		count += ft_int_putnbr_fd(n % 10, fd);
	}
	if (n < 10)
		count += ft_int_putchar_fd((char)n + '0', fd);
	return (count);
}
