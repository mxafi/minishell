/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_heredoc_validation_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 11:33:33 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/23 16:56:41 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sig_heredoc(int sig)
{
	ioctl(0, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	if (sig == SIGINT)
		kill(g_minishell->pid_single, SIGINT);
	else if (sig == SIGQUIT)
	{
		kill(g_minishell->pid_single, SIGQUIT);
		ft_putstr_fd("Quit: 3", 1);
	}
}
