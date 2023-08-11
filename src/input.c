/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 21:08:47 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/11 09:26:12 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ctrl_c(int sig)
{
	(void)sig;
	ioctl(0, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	ignore_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c);
}

void	restore_signal_defaults(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

void	toggle_echoctl(void)
{
	struct termios	termios_attributes;

	tcgetattr(STDIN_FILENO, &termios_attributes);
	termios_attributes.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_attributes);
}

char	*get_input(void)
{
	char	*line_read;

	ignore_signals();
	toggle_echoctl();
	line_read = readline("shellfish🦞> ");
	if (!line_read)
	{
		toggle_echoctl();
		exit(g_minishell->exit_status);
	}
	if (*line_read)
		add_history(line_read);
	restore_signal_defaults();
	toggle_echoctl();
	return (line_read);
}
