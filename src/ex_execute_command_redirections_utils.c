/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_execute_command_redirections_utils.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:02:36 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/24 11:03:15 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	open_redir_file(const char *file_path, int flags)
{
	const int	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	const int	file = open(file_path, flags, mode);

	if (file == -1)
	{
		ft_putstr_fd("shellfishy: ", 2);
		perror(file_path);
	}
	return (file);
}

void	execute_command_redirections_cleanup(t_ast_node *node)
{
	int					current_redir_idx;
	t_ast_redir_type	c_type;
	t_redir				*c_redir;

	current_redir_idx = 0;
	while (current_redir_idx < node->redir_count)
	{
		c_redir = node->redirections[current_redir_idx];
		c_type = c_redir->type;
		close(c_redir->file_descriptor);
		if (c_type == AST_HEREDOC)
			unlink(c_redir->argument);
		else if (c_type == AST_NULL_REDIR)
		{
			unlink(c_redir->argument);
			g_minishell->exit_status = 1;
		}
		if (c_redir->file_descriptor == -1)
			exit(1);
		current_redir_idx++;
	}
}
