/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_undefined.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:47:23 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/25 15:11:26 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execute_safe_undefined(t_ast_node *node)
{
	if (g_minishell->is_pipeline)
	{
		execute_command_redirections(node);
		execute_command_redirections_cleanup(node);
		exit(g_minishell->exit_status);
	}
	else
	{
		if (wrap_fork(&g_minishell->pid_single) == 0)
		{
			dup2(-1, STDIN_FILENO);
			dup2(-1, STDOUT_FILENO);
			execute_command_redirections(node);
			execute_command_redirections_cleanup(node);
			exit(g_minishell->exit_status);
		}
		waitpid(g_minishell->pid_single, &g_minishell->termination_status, 0);
		g_minishell->exit_status = ret_exit_status(
				g_minishell->termination_status);
	}
}
