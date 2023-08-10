/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_heredoc_validation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:26:00 by lclerc            #+#    #+#             */
/*   Updated: 2023/08/10 11:46:10 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexer.h"

char	*get_input_heredoc(int is_heredoc)
{
	char	*line_read;

	ignore_signals();
	toggle_echoctl();
	line_read = readline("> ");
	if (!line_read)
		exit(0); // Handle C-d, should return the exit code of the previous command.
	if (*line_read && !is_heredoc)
		add_history(line_read);
	restore_signal_defaults();
	toggle_echoctl();
	return (line_read);
}


