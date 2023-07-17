/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:08:34 by malaakso          #+#    #+#             */
/*   Updated: 2022/12/15 13:27:19 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	handle_double_malloc_fail(char *stash, char *buffer)
{
	if (!stash && !buffer)
		return (0);
	if (!stash)
	{
		free(buffer);
		return (0);
	}
	if (!buffer)
	{
		free(stash);
		return (0);
	}
	return (1);
}

static char	*append_str(char *input, char *original, size_t input_len)
{
	char	*final;
	size_t	original_len;
	size_t	final_len;

	if (!input_len)
		return (original);
	original_len = 0;
	while (original[original_len])
		original_len++;
	final_len = input_len + original_len;
	final = ft_strndup(original, final_len);
	if (!final)
		return (NULL);
	(void)ft_strlcat(final, input, final_len + 1);
	free(original);
	return (final);
}

static char	*ret_line(char *stash, ssize_t read_value)
{
	char	*line;
	char	*chr;
	size_t	i;

	if ((!read_value && !*stash) || read_value < 0)
		return (NULL);
	chr = ft_strchr(stash, '\n');
	if (!chr)
		return (ft_strdup(stash));
	i = 0;
	while (stash[i] != '\n')
		i++;
	line = ft_calloc(i + 2, 1);
	if (!line)
		return (NULL);
	while (i > 0)
	{
		line[i] = stash[i];
		i--;
	}
	line[i] = stash[i];
	return (line);
}

static char	*trim_stash(char *stash, ssize_t read_value)
{
	char	*new_stash;
	char	*chr;
	size_t	len;

	if (read_value <= 0)
	{
		free(stash);
		return (NULL);
	}
	chr = ft_strchr(stash, '\n');
	if (!chr && read_value > 0)
	{
		new_stash = ft_calloc(1, 1);
		free(stash);
		return (new_stash);
	}
	chr++;
	len = 0;
	while (chr[len])
		len++;
	new_stash = ft_strndup(chr, len);
	free (stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	char				*buffer;
	ssize_t				n_bytes_read;
	static char			*stash;
	char				*line;

	if (BUFFER_SIZE < 1 || fd < 0 || fd > 1000 || read(fd, NULL, 0) < 0)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!stash)
		stash = ft_calloc(1, 1);
	if (!handle_double_malloc_fail(stash, buffer))
		return (NULL);
	n_bytes_read = BUFFER_SIZE;
	while (!ft_strchr(stash, '\n') && n_bytes_read == BUFFER_SIZE)
	{
		n_bytes_read = read(fd, buffer, BUFFER_SIZE);
		stash = append_str(buffer, stash, n_bytes_read);
		if (!handle_double_malloc_fail(stash, buffer))
			return (NULL);
	}
	free(buffer);
	line = ret_line(stash, n_bytes_read);
	stash = trim_stash(stash, n_bytes_read);
	return (line);
}
