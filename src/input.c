/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 21:08:47 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/24 16:21:47 by malaakso         ###   ########.fr       */
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
	char	*hist_line;

	ignore_signals();
	toggle_echoctl();
	line_read = readline("shellfish🦞> ");
	restore_signal_defaults();
	toggle_echoctl();
	if (!line_read)
		exit(0);
	if (*line_read)
	{
		hist_line = ft_strdup(line_read);
		if (!hist_line)
			exit(1);
		add_history(hist_line);
		free(hist_line);
	}
	return (line_read);
}
