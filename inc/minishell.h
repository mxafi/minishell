/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:34:09 by malaakso          #+#    #+#             */
/*   Updated: 2023/06/19 15:23:30 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <termcap.h>
# include <termios.h>

# include "libft.h"
# include "input.h"

typedef struct s_minishell
{
	int	exit_code;
}	t_minishell;

void	rl_replace_line(const char *text, int clear_undo);

void	display_prompt(void);

#endif
