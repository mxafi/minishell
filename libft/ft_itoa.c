/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:04:29 by malaakso          #+#    #+#             */
/*   Updated: 2022/11/06 21:02:43 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ret_int_len(long n)
{
	int		len;

	len = 0;
	if (n < 0)
	{
		len++;
		n = n * -1;
	}
	while (n > 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static void	populate_int_str(char *int_str, int n_len, long n_long)
{
	int_str[n_len] = '\0';
	if (n_long < 0)
	{
		n_long *= -1;
		int_str[0] = '-';
	}
	n_len--;
	while (n_long > 9)
	{
		int_str[n_len] = (n_long % 10) + '0';
		n_len--;
		n_long = n_long / 10;
	}
	int_str[n_len] = n_long + '0';
}

char	*ft_itoa(int n)
{
	char	*int_str;
	int		n_len;
	long	n_long;

	n_long = (long)n;
	n_len = ret_int_len(n_long);
	if (n_len == 0)
	{
		int_str = ft_calloc(2, 1);
		if (!int_str)
			return (0);
		int_str[0] = '0';
		return (int_str);
	}
	int_str = malloc(n_len + 1);
	if (!int_str)
		return (0);
	populate_int_str(int_str, n_len, n_long);
	return (int_str);
}
