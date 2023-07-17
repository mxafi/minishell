/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:34:09 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/17 09:52:05 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Provides constants for system limits, such as maximum path length.
# include <limits.h>

// Contains general-purpose functions like malloc, free, exit, getenv.
# include <stdlib.h>

// Includes write, access, read, close, fork, getcwd, chdir, stat, lstat,
// fstat, unlink, execve, dup, dup2, pipe, isatty, ttyname, tcsetattr,
// tcgetattr, and others.
# include <unistd.h>

// Necessary includes for readline.
# include <readline/readline.h>
# include <readline/history.h>

// Includes signal, sigaction, sigemptyset, sigaddset, kill.
# include <signal.h>

// Includes open.
# include <fcntl.h>

// Includes sterror.
# include <string.h>

// Defines the errno global variable and various error codes.
# include <errno.h>

// Includes tcsetattr and tcgetattr specific to the current terminal.
# include <termios.h>

// User defined headers
# include "../libft/libft.h"
# include "input.h"
# include "env.h"
# include "lexer.h"

// Includes assert functions
# include "assert.h"

typedef struct s_minishell
{
	int		exit_code;
	char	**envp;
}	t_minishell;

t_minishell	*g_minishell;

// Necessary function prototype for readline.
void	rl_replace_line(const char *text, int clear_undo);

// Function prototypes from minishell.c
void	display_prompt(void);

/*
 * Contained in lexer.c
 */
int	lexer(char	*input);

#endif
