/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:59:04 by lclerc            #+#    #+#             */
/*   Updated: 2023/06/15 13:59:06 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../inc/lexer.h"

const char	*ft_strpbrk(const char	*string, const char	*delimiters)
{
	int			i;
	int			j;

	i = 0;
	while (string[i] != '\0')
	{
		j = 0;
		while (delimiters[j] != '\0')
		{
			if (string[i] == delimiters[j])
				return ((char *) (string + i - 1));
			j++;
		}
		i++;
	}
	return (NULL);
}

