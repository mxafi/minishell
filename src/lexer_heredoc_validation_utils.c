/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_heredoc_validation_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 11:33:33 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/24 16:38:03 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Handles signals related to heredoc process.
 * 
 * @param sig The signal that was received.
 */
void	sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{	
		kill(g_minishell->pid_single, SIGINT);
	}
}

char	*heredoc_get_line(void)
{
	char	*line_read;

	toggle_echoctl();
	signal(SIGQUIT, SIG_IGN);
	line_read = readline("> ");
	signal(SIGQUIT, SIG_DFL);
	toggle_echoctl();
	return (line_read);
}
