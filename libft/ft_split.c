/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:48:19 by malaakso          #+#    #+#             */
/*   Updated: 2022/11/04 19:28:23 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_count_f(char const *s, char c)
{	
	int		word_flag;
	size_t	i;
	size_t	count;

	word_flag = 0;
	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			word_flag = 0;
		else if (word_flag == 0)
		{
			word_flag = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static size_t	char_count(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i] != 0)
		i++;
	return (i);
}

static int	create_word(char **matrix, char const *s, char c, size_t i)
{
	size_t	current_char_count;

	current_char_count = char_count(s, c);
	matrix[i] = malloc(current_char_count + 1);
	if (!matrix[i])
	{
		while (i)
		{
			free(matrix[i]);
			i--;
		}
		free(matrix[i]);
		free(matrix);
		return (0);
	}
	matrix[i][current_char_count] = 0;
	current_char_count = 0;
	while (s[current_char_count] && s[current_char_count] != c)
	{
		matrix[i][current_char_count] = s[current_char_count];
		current_char_count++;
	}
	return (1);
}

static int	pop_words(char **m, char const *s, char c, size_t w_c)
{
	size_t	i;
	int		word_flag;

	i = 0;
	word_flag = 0;
	while (i < w_c && *s)
	{
		if (*s == c)
			word_flag = 0;
		else if (word_flag == 0)
		{
			word_flag = 1;
			if (!create_word(m, s, c, i))
				return (0);
			i++;
		}
		s++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t	word_count;
	char	**matrix;

	if (!s)
		return (0);
	word_count = word_count_f(s, c);
	if (!word_count)
	{
		matrix = malloc(sizeof(*matrix));
		if (!matrix)
			return (0);
		matrix[0] = 0;
		return (matrix);
	}
	matrix = malloc((word_count + 1) * sizeof(*matrix));
	if (!matrix)
		return (0);
	matrix[word_count] = 0;
	if (!pop_words(matrix, s, c, word_count))
		return (0);
	return (matrix);
}
