/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 21:08:47 by malaakso          #+#    #+#             */
/*   Updated: 2023/06/14 12:34:47 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(void)
{
	char	*line_read;

	line_read = readline("shellfish🦞> ");
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}
