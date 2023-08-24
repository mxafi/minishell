/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_execute_command_redirections.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:00:44 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/24 11:03:11 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execute_command_redirections_infile(t_redir *c_redir)
{
	c_redir->file_descriptor = open_redir_file(c_redir->argument, O_RDONLY);
	dup2(c_redir->file_descriptor, STDIN_FILENO);
}

void	execute_command_redirections_outfile(t_redir *c_redir)
{
	c_redir->file_descriptor = open_redir_file(
			c_redir->argument, O_CREAT | O_WRONLY | O_TRUNC);
	dup2(c_redir->file_descriptor, STDOUT_FILENO);
}

void	execute_command_redirections_append(t_redir *c_redir)
{
	c_redir->file_descriptor = open_redir_file(
			c_redir->argument, O_CREAT | O_WRONLY | O_APPEND);
	dup2(c_redir->file_descriptor, STDOUT_FILENO);
}

void	execute_command_redirections_heredoc(t_redir *c_redir)
{
	c_redir->file_descriptor = open_redir_file(c_redir->argument, O_RDONLY);
	dup2(c_redir->file_descriptor, STDIN_FILENO);
}

void	execute_command_redirections(t_ast_node *node)
{
	int					current_redir_idx;
	t_ast_redir_type	c_type;
	t_redir				*c_redir;

	current_redir_idx = 0;
	while (current_redir_idx < node->redir_count)
	{
		c_redir = node->redirections[current_redir_idx];
		c_type = c_redir->type;
		if (c_type == AST_INFILE)
			execute_command_redirections_infile(c_redir);
		else if (c_type == AST_OUTFILE)
			execute_command_redirections_outfile(c_redir);
		else if (c_type == AST_APPEND)
			execute_command_redirections_append(c_redir);
		else if (c_type == AST_HEREDOC)
			execute_command_redirections_heredoc(c_redir);
		if (c_redir->file_descriptor == -1)
		{
			execute_command_redirections_cleanup(node);
			break ;
		}
		current_redir_idx++;
	}
}
